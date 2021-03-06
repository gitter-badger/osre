/*-----------------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2015-2016 OSRE ( Open Source Render Engine ) by Kim Kulling

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
-----------------------------------------------------------------------------------------------*/
#pragma once

#include "vulkan.h"
#include "VlkCommon.h"

#include <cppcore/Container/TArray.h>

namespace OSRE {

namespace Platform {
    struct LibHandle;
}

namespace RenderBackend {

class VlkRenderBackend {
    enum class State {
        Uninitialized = 0,
        Initialized
    };

public:
    VlkRenderBackend();
    ~VlkRenderBackend();
    bool create();
    VkDevice getDevice() const;
    const VlkSwapChainParameters getSwapChain() const;

private:
    bool loadVulkanLib();
    bool loadExportedEntryPoints();
    bool createInstance();
    bool loadInstanceLevelEntryPoints();
    bool createPresentationSurface();
    bool createDevice();
    bool loadDeviceLevelEntryPoints();
    bool getDeviceQueue();
    bool createSwapChain();
    bool loadGlobalLevelEntryPoints();
    bool createRenderPass();
    bool createFramebuffers();
    bool checkPhysicalDeviceProperties( VkPhysicalDevice physical_device, uint32_t &selected_graphics_queue_family_index, uint32_t &selected_present_queue_family_index );

private:
    VlkCommonParameters              m_vulkan;
    VkRenderPass                     m_renderPass;
    CPPCore::TArray<VkFramebuffer>   m_framebuffers;
    VkPipeline                       m_graphicsPipeline;
    VkSemaphore                      m_imageAvailableSemaphore;
    VkSemaphore                      m_renderingFinishedSemaphore;
    VkCommandPool                    m_graphicsCommandPool;
    CPPCore::TArray<VkCommandBuffer> m_graphicsCommandBuffers;
    Platform::LibHandle             *m_handle;
    State                            m_state;
};

} // Namespace RenderBackend
} // Namespace OSRE
