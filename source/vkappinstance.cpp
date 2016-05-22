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

#include <vkappinstance.h>
#include <cassert>
#include <iostream>

VKAppInstance::VKAppInstance()
{
    /*Build collection of available instance layers per Vulkan API version*/
    
    
    //Vulkan API 1.0.11
    m_instanceLayerCollection.push_back({
        "VK_LAYER_GOOGLE_threading", "VK_LAYER_LUNARG_core_validation",
        "VK_LAYER_LUNARG_object_tracker", "VK_LAYER_LUNARG_parameter_validation",
        "VK_LAYER_LUNARG_standarrd_validation", "VK_LAYER_LUNARG_swapchain",
        "VK_LAYER_LUNARG_device_limits", "VK_LAYER_LUNARG_image"
    });

    //Vulkan API 1.0.8
    m_instanceLayerCollection.push_back({
        "VK_LAYER_GOOGLE_threading", "VK_LAYER_LUNARG_core_validation",
        "VK_LAYER_LUNARG_object_tracker", "VK_LAYER_LUNARG_parameter_validation",
        "VK_LAYER_LUNARG_standard_validation", "VK_LAYER_LUNARG_swapchain",
        "VK_LAYER_LUNARG_device_limits", "VK_LAYER_LUNARG_image"
    });

    m_instance = nullptr;
}

VKAppInstance::~VKAppInstance()
{
    if(m_instance != VK_NULL_HANDLE)
    {
        vkDestroyInstance(m_instance, nullptr);
    }
}

const std::vector<const char*>& VKAppInstance::EnabledLayerNames() const
{
    return m_enabledLayerNames;
}

const std::vector<const char*>& VKAppInstance::EnabledExtNames() const
{
    return m_enabledExtNames;
}

bool VKAppInstance::Initialize(std::string title)
{
    VkResult res = VK_SUCCESS;

    if(!CheckInstanceExtensions())
        return false;

    VkApplicationInfo info;
    info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    info.pNext = nullptr;
    info.pApplicationName = title.c_str();
    info.applicationVersion = 0;
    info.pEngineName = "VulkanExamples";
    info.engineVersion = 0;
    info.apiVersion = VK_MAKE_VERSION(1, 0, 11);

    for(auto layers : m_instanceLayerCollection)
    {
        m_enabledLayerNames = layers;

        VkInstanceCreateInfo cInfo;
        cInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        cInfo.pNext = nullptr;
        cInfo.flags = 0;
        cInfo.pApplicationInfo = &info;
        cInfo.enabledLayerCount = static_cast<uint32_t>(layers.size());
        cInfo.ppEnabledLayerNames = &layers[0];
        cInfo.enabledExtensionCount = m_enabledExtNames.size();
        cInfo.ppEnabledExtensionNames = &m_enabledExtNames[0];

        res = vkCreateInstance(&cInfo, nullptr, &m_instance);
        if(res == VK_SUCCESS)
            break;
        else
            std::cerr << "Failed to create Vulkan instance." << std::endl;
    }

    return true;
}

bool VKAppInstance::CheckInstanceExtensions()
{
    VkResult res = VK_SUCCESS;
    
    uint32_t extCount = 0;
    res = vkEnumerateInstanceExtensionProperties(nullptr, &extCount, nullptr);
    assert(!res);

    if(extCount > 0)
    {
        std::vector<VkExtensionProperties> extensions(extCount);
        res = vkEnumerateInstanceExtensionProperties(nullptr, &extCount, &extensions[0]);
        assert(!res);

        for(auto ext : extensions)
        {
            if(!strcmp(VK_KHR_SURFACE_EXTENSION_NAME, ext.extensionName))
                m_enabledExtNames.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
#ifdef _WIN32

#else
            if(!strcmp(VK_KHR_XLIB_SURFACE_EXTENSION_NAME, ext.extensionName))
                m_enabledExtNames.push_back(VK_KHR_XLIB_SURFACE_EXTENSION_NAME);
#endif            

            if(!strcmp(VK_EXT_DEBUG_REPORT_EXTENSION_NAME, ext.extensionName))
                m_enabledExtNames.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);


            assert(m_enabledExtNames.size() < 64);
        }

    }

    return true;
}


