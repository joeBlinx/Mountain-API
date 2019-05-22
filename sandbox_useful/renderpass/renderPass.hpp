//
// Created by joe on 5/10/19.
//

#ifndef SANDBOX_RENDERPASS_HPP
#define SANDBOX_RENDERPASS_HPP


#include <vulkan/vulkan.h>
#include <array>
#include <log.hpp>
#include <utility>
enum subpass_attachment: unsigned {
	COLOR = 1u,
	DEPTH = 1u << 2u,
	STENCIL = 1u << 3u
};

struct SubPass
{
	bool attachment_color; // must be filled with subpass_attachment
    unsigned attachment_depth_stencil = 0; // must be filled with subpass_attachment
};
struct RenderPass {
	~RenderPass();

	template<SubPass ...attachment>
	static RenderPass create(VkDevice device, VkFormat const &swap_chain_image_format);
	VkRenderPass get_renderpass() {return _renderpass ;}
private:

	VkDevice _device = nullptr;
	RenderPass(VkDevice device, VkRenderPassCreateInfo renderpass_info);
	VkRenderPass _renderpass = nullptr;
};



template<unsigned attach>
constexpr VkImageLayout get_corresponding_attachment();

template<>
constexpr VkImageLayout get_corresponding_attachment<(unsigned)subpass_attachment::COLOR>()
{
	return VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
}

template<>
constexpr VkImageLayout get_corresponding_attachment<(unsigned)subpass_attachment::DEPTH>()
{
	return VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
}
template<>
constexpr VkImageLayout get_corresponding_attachment<(unsigned)subpass_attachment::STENCIL>()
{
	return get_corresponding_attachment<(unsigned)subpass_attachment::DEPTH>();
}
template<unsigned attach>
constexpr VkAttachmentDescription
fill_attachment(VkAttachmentDescription &attachement, VkFormat const&, VkFormat const&)
{
	return attachement;
}

template<>
constexpr VkAttachmentDescription
fill_attachment<(unsigned)subpass_attachment::COLOR>(VkAttachmentDescription &attachement, VkFormat const&color,
                                                     VkFormat const&)
{
	attachement.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	attachement.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	attachement.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    attachement.format = color;
	return attachement;
}

template<>
constexpr VkAttachmentDescription
fill_attachment<(unsigned)subpass_attachment::DEPTH>(VkAttachmentDescription &attachement, VkFormat const&,
                                                     VkFormat const&depth)
{
    attachement.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachement.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	attachement.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    attachement.format = depth;
	return attachement;
}
template<>
constexpr VkAttachmentDescription
fill_attachment<(unsigned)subpass_attachment::STENCIL>(VkAttachmentDescription &attachement, VkFormat const&,
                                                       VkFormat const& depth)
{
    attachement.format = depth;
	attachement.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	attachement.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	attachement.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
	return attachement;
}
template<int n, unsigned reference>
constexpr VkAttachmentReference get_attachement()
{
	return VkAttachmentReference
			{
					.attachment = n,
					.layout = get_corresponding_attachment<reference>()
			};
}
template<unsigned ...reference, std::size_t... I>
constexpr std::array<VkAttachmentReference, sizeof...(I)> a2t_impl(std::index_sequence<I...>)
{
	return { get_attachement<I, reference>()...};
}

template<unsigned ...references, typename Indices = std::make_index_sequence<sizeof...(references)>>
constexpr std::array<VkAttachmentReference, sizeof...(references)> a2t()
{
	return a2t_impl<references...>(Indices{});
}

template<unsigned ... references>
constexpr std::array<VkAttachmentReference, sizeof...(references)> pack()
{
	return a2t<references...>();

}
template<SubPass subpass, template <unsigned> class Function, class ... Args>
constexpr decltype(auto) apply_for_all_case( Args &...args)
{
	auto color = Function<subpass.attachment_color & subpass_attachment::COLOR>()(args...);
	Function<subpass.attachment_depth_stencil & subpass_attachment::DEPTH>()(args...);
	return std::pair{color, Function<subpass.attachment_depth_stencil & subpass_attachment::STENCIL>()(args...)};

}
template<unsigned N>
struct wrapper
{
	constexpr VkAttachmentDescription
    operator()(VkAttachmentDescription &attachmentDescription, VkFormat const& color, VkFormat const& depth)
	{
		return fill_attachment<N>(attachmentDescription, color, depth);
	}
};
template<SubPass... attachment>
constexpr
std::array<std::pair<VkAttachmentDescription, VkAttachmentDescription> , sizeof...(attachment)>
        fill_attachments (VkFormat const &color, VkFormat const &depth)
{
	VkAttachmentDescription attachment_desc{
			.flags = 0,
			.format = VkFormat{},
			.samples = VK_SAMPLE_COUNT_1_BIT,
			.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
			.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
			.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
			.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
			.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
			.finalLayout = VK_IMAGE_LAYOUT_UNDEFINED
	};



	return {apply_for_all_case<attachment, wrapper>(attachment_desc, color, depth)...};
}
template<SubPass... attachment>
RenderPass RenderPass::create(VkDevice device, VkFormat const &swap_chain_image_format) {

	//constexpr auto all_attachment_ref = pack<attachment.attachment...>();
    auto attachments_desc = fill_attachments<attachment...>(swap_chain_image_format, swap_chain_image_format);

//	VkAttachmentDescription colorAttachment = {};
//	colorAttachment.format = swap_chain_image_format;
//	colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
//	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
//	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
//	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
//	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
//	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
//	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentReference colorAttachmentRef = {};
	colorAttachmentRef.attachment = 0;
	colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkSubpassDescription subpass = {};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &colorAttachmentRef;

	VkSubpassDependency dependency = {};
	dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	dependency.dstSubpass = 0;
	dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.srcAccessMask = 0;
	dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

	VkRenderPassCreateInfo renderPassInfo = {};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.attachmentCount = attachments_desc.size();
	renderPassInfo.pAttachments = reinterpret_cast<VkAttachmentDescription*>(attachments_desc.data());
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpass;
	renderPassInfo.dependencyCount = 1;
	renderPassInfo.pDependencies = &dependency;

	return RenderPass(device, renderPassInfo);
}



#endif //SANDBOX_RENDERPASS_HPP
