#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <systemd/sd-bus.h>
#include <iostream>

namespace Test{
    void service(const std::string& text);
    void finish();
}
