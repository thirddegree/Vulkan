/*
*    The MIT License (MIT)
*
*    Copyright (c) 2016 ThirdDegree 
*
*    Permission is hereby granted, free of charge, to any person obtaining a copy
*    of this software and associated documentation files (the "Software"), to deal
*    in the Software without restriction, including without limitation the rights
*    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*    copies of the Software, and to permit persons to whom the Software is
*    furnished to do so, subject to the following conditions:
*
*    The above copyright notice and this permission notice shall be included in all
*    copies or substantial portions of the Software.
*
*    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*    SOFTWARE.
*/

#pragma once

#include <platform.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <string>

extern PFN_vkGetPhysicalDeviceSurfaceSupportKHR 
    fpGetPhysicalDeviceSurfaceSupportKHR;
extern PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR
    fpGetPhysicalDeviceSurfaceCapabilitiesKHR;
extern PFN_vkGetPhysicalDeviceSurfaceFormatsKHR
    fpGetPhysicalDeviceSurfaceFormatsKHR;
extern PFN_vkGetPhysicalDeviceSurfacePresentModesKHR
    fpGetPhysicalDeviceSurfacePresentModesKHR;
extern PFN_vkCreateDebugReportCallbackEXT
    fpCreateDebugReportCallback; 

class VKAppInstance
{
public:
    VKAppInstance();

    ~VKAppInstance();

    bool Initialize(std::string title);

    const std::vector<const char*>& EnabledLayerNames() const;
    const std::vector<const char*>& EnabledExtNames() const;

private:
    VkInstance                               m_instance;
    std::vector<std::vector<const char*>>    m_instanceLayerCollection;
    std::vector<const char*>                 m_enabledLayerNames;
    std::vector<const char*>                 m_enabledExtNames;

    bool CheckInstanceExtensions();
};
