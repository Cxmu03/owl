#include "owl/owl.hpp"

int main() {
    owl::Window window({500, 500}, "Poggers");
    window.SetClearColor({255, 0, 0, 1.f});

    window.Run([](){});
}