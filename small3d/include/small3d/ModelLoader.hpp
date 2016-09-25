/*
 *  ModelLoader.hpp
 *
 *  Created on: 2014/11/12
 *      Author: Dimitri Kourkoulis
 *     License: BSD 3-Clause License (see LICENSE file)
 */
#pragma once

#include <memory>
#include "Logger.hpp"
#include "Model.hpp"

namespace small3d {

  /**
   * @class	ModelLoader
   *
   * @brief	Class that loads a model from a file, into a Model object. (abstract class)
   *
   */

  class ModelLoader {

  public:

    /**
     * Default constructor
     *
     */

    ModelLoader() = default;

    /**
     * Destructor
     *
     */

    virtual ~ModelLoader() = default;

    /**
     * Loads a model from the given file into the model object.
     *
     * @param	filename	Name of the file in which the model is stored.
     * @param	model   	The model.
     */

    virtual void load(string filename, Model &model);
  };
}
