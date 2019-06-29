#pragma once
#include "Layer.h"

namespace King {
  class KING_API LayerStack
  {
  public:
    LayerStack();
    ~LayerStack();
    void pushLayer(Layer* layer);
    void pushOverlay(Layer* layer);
    void popLayer(Layer* layer);
    void popOverlay(Layer* layer);

    std::vector<Layer*>::iterator begin() { return m_layers.begin(); };
    std::vector<Layer*>::iterator end() { return m_layers.end(); };

  private:
    std::vector<Layer*> m_layers;
    unsigned int m_layerInsertIndex = 0;
  };
}



