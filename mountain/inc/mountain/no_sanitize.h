//
// Created by stiven_perso on 1/28/21.
//

#ifndef SANDBOX_NO_SANITIZE_H
#define SANDBOX_NO_SANITIZE_H
#if defined(__GNUG__) || defined(__clang__)
#define NO_SANITIZE __attribute__((no_sanitize("address")))
#else
#define NO_SANITIZE
#endif
#endif //SANDBOX_NO_SANITIZE_H
