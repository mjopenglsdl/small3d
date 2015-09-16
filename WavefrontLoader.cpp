/*
 *  WavefrontLoader.cpp
 *
 *  Created on: 2014/11/12
 *      Author: Dimitri Kourkoulis
 *              http://dimitros.be
 *     License: BSD 3-Clause License (see LICENSE file)
 */

#include "WavefrontLoader.hpp"
#include "Exception.hpp"
#include <fstream>
#include <unordered_map>
#include "GetTokens.hpp"
#include <miguel/sdl2/include/SDL.h>

using namespace std;

namespace small3d {

  void WavefrontLoader::loadVertexData() {
    // 4 components per vertex
    model->vertexDataSize = (int) (4 * vertices.size() * sizeof(float));

    model->vertexData.clear();

    int idx = 0;
    for (vector<vector<float> >::iterator vertex = vertices.begin(); vertex != vertices.end(); ++vertex) {
      for (int coordIdx = 0; coordIdx != 3; ++coordIdx) {
        model->vertexData.push_back(vertex->at(coordIdx));
        ++idx;
      }
      model->vertexData.push_back(1.0f);
      ++idx;
    }
  }

  void WavefrontLoader::loadIndexData() {
    // 3 indices per face
    int numIndexes = facesVertexIndices.size() * 3;
    model->indexDataSize = numIndexes * sizeof(int);

    model->indexData.clear();

    for (vector<vector<int> >::iterator face = facesVertexIndices.begin(); face != facesVertexIndices.end(); ++face) {

      for (int indexIdx = 0; indexIdx != 3; ++indexIdx) {
        model->indexData.push_back(face->at(indexIdx) - 1); // -1 because Wavefront indexes
        // are not 0 based

      }
    }
  }

  void WavefrontLoader::loadNormalsData() {

    // Create an array of normal components which corresponds
    // by index to the array of vertex components


    if (model->vertexData.size() == 0) {
      throw Exception(
          "There are no vertices or vertex data has not yet been created.");
    }

    // 3 components per vertex (a single index for vertices, normals and texture coordinates
    // is passed to OpenGL, so normals data will be aligned to vertex data according to the
    // vertex index)

    model->normalsDataSize = (int) (3 * vertices.size() * sizeof(float));

    model->normalsData = vector<float>(3 * vertices.size(), 0.0f);

    int faceVertexArrayIndex = 0;
    for (vector<vector<int> >::iterator faceVertexIndex = facesVertexIndices.begin();
         faceVertexIndex != facesVertexIndices.end(); ++faceVertexIndex) {
      for (int vertexIndex = 0; vertexIndex != 3; ++vertexIndex) {

        for (int normalsDataComponent = 0; normalsDataComponent != 3;
             ++normalsDataComponent) {
          model->normalsData[3 * (faceVertexIndex->at(vertexIndex) - 1)
                             + normalsDataComponent] =
              normals.at(
                  facesNormalIndices.at(faceVertexArrayIndex)[vertexIndex]
                  - 1)[normalsDataComponent];
        }
      }
      ++faceVertexArrayIndex;
    }
  }

  void WavefrontLoader::loadTextureCoordsData() {
    if (!textureCoords.empty()) {
      // Create an array of texture coordinates components which corresponds
      // by index to the array of vertex components

      if (model->vertexData.size() == 0) {
        throw Exception(
            "There are no vertices or vertex data has not yet been created.");
      }

      // 2 components per vertex (a single index for vertices, normals and texture coordinates
      // is passed to OpenGL, so texture coordinates data will be aligned to vertex data according
      // to the vertex index)
      model->textureCoordsDataSize = 2 * vertices.size() * sizeof(float);

      model->textureCoordsData = vector<float>(2 * vertices.size());

      int faceVertexArrayIndex = 0;

      for (vector<vector<int> >::iterator faceVertexIndex = facesVertexIndices.begin();
           faceVertexIndex != facesVertexIndices.end();
           ++faceVertexIndex) {
        for (int vertexIndex = 0; vertexIndex != 3; ++vertexIndex) {

          for (int textureCoordsComponent = 0;
               textureCoordsComponent != 2; ++textureCoordsComponent) {
            model->textureCoordsData[2 * (faceVertexIndex->at(vertexIndex) - 1)
                                     + textureCoordsComponent] =
                textureCoords.at(
                    (unsigned long) (textureCoordsIndices.at(faceVertexArrayIndex)[vertexIndex]
                                     - 1))[textureCoordsComponent];
          }
        }
        ++faceVertexArrayIndex;
      }
    }
  }

  void WavefrontLoader::correctDataVectors() {

    unique_ptr<unordered_map<int, int> > vertexUVPairs(new unordered_map<int, int>());

    int numIndexes = (int) facesVertexIndices.size();

    for (int idx = 0; idx < numIndexes; ++idx) {

      for (int vertexIndex = 0; vertexIndex != 3; ++vertexIndex) {

        unordered_map<int, int>::iterator vertexUVPair = vertexUVPairs->find(facesVertexIndices[idx][vertexIndex]);
        if (vertexUVPair != vertexUVPairs->end()) {
          if (vertexUVPair->second != textureCoordsIndices.at(idx)[vertexIndex]) {
            // duplicate corresponding vertex data entry and point the vertex index to the new tuple
            vector<float> v;
            // -1 because at this stage the indexes are still as exported from Blender, meaning 1-based
            // and not 0-based
            v.push_back(vertices[facesVertexIndices[idx][vertexIndex] - 1][0]);
            v.push_back(vertices[facesVertexIndices[idx][vertexIndex] - 1][1]);
            v.push_back(vertices[facesVertexIndices[idx][vertexIndex] - 1][2]);
            vertices.push_back(v);

            facesVertexIndices[idx][vertexIndex] = (int) vertices.size();

            vertexUVPairs->insert(
                make_pair(facesVertexIndices[idx][vertexIndex], textureCoordsIndices[idx][vertexIndex]));
          }
          // So we don't add a pair if the exact same pair already exists. We do if it does not (see below) or if
          // the vertex index number exists in a pair with a different texture coordinates index number (see above)
        }
        else {
          vertexUVPairs->insert(
              make_pair(facesVertexIndices[idx][vertexIndex], textureCoordsIndices[idx][vertexIndex]));
        }
      }
    }

  }

  void WavefrontLoader::init() {
    vertices.clear();
    facesVertexIndices.clear();
    normals.clear();
    facesNormalIndices.clear();
    textureCoords.clear();
    textureCoordsIndices.clear();
    this->model = NULL;
  }

  void WavefrontLoader::clear() {
    vertices.clear();
    facesVertexIndices.clear();
    normals.clear();
    facesNormalIndices.clear();
    textureCoords.clear();
    textureCoordsIndices.clear();

    this->model = NULL;
  }


  WavefrontLoader::WavefrontLoader() {
    init();

  }

  WavefrontLoader::~WavefrontLoader() {
    clear();
  }

  void WavefrontLoader::load(const string &fileLocation, Model &model) {

    ifstream file((SDL_GetBasePath() + fileLocation).c_str());
    string line;
    if (file.is_open()) {
      init();
      this->model = &model;

      while (getline(file, line)) {
        if (line[0] == 'v' || line[0] == 'f') {
          string tokens[4]; // Max 4 such tokens in the specific kind of Wavefront file

          int numTokens = getTokens(line, ' ', tokens);

          int idx = 0;

          if (line[0] == 'v' && line[1] == 'n') {
            // get vertex normal
            vector<float> vn;

            for (int tokenIdx = 0; tokenIdx < numTokens; ++tokenIdx) {
              string t = tokens[tokenIdx];
              if (idx > 0)   // The first token is the vertex normal indicator
              {
                vn.push_back((float) atof(t.c_str()));
              }
              ++idx;
            }
            normals.push_back(vn);
          }
          else if (line[0] == 'v' && line[1] == 't') {
            vector<float> vt;

            for (int tokenIdx = 0; tokenIdx < numTokens; ++tokenIdx) {
              string t = tokens[tokenIdx];
              if (idx > 0)   // The first token is the vertex texture coordinate indicator
              {
                vt.push_back((float) atof(t.c_str()));
              }
              ++idx;
            }

            vt[1] = 1.0f - vt[1]; // OpenGL's y direction for textures is the opposite of that
            // of Blender's, so an inversion is needed
            textureCoords.push_back(vt);
          }
          else if (line[0] == 'v') {
            // get vertex
            vector<float> v;

            for (int tokenIdx = 0; tokenIdx < numTokens; ++tokenIdx) {
              string t = tokens[tokenIdx];
              if (idx > 0)   // The first token is the vertex indicator
              {
                v.push_back((float) atof(t.c_str()));
              }
              ++idx;
            }
            vertices.push_back(v);
          }
          else {
            // get vertex index
            vector<int> v = vector<int>(3, 0);
            vector<int> n;
            vector<int> textC;

            for (int tokenIdx = 0; tokenIdx < numTokens; ++tokenIdx) {
              string t = tokens[tokenIdx];

              if (idx > 0)   // The first token is face indicator
              {
                if (t.find("//") != string::npos)   // normal index contained in the string
                {
                  v[idx - 1] = atoi(
                      t.substr(0, t.find("//")).c_str());
                  n.push_back(atoi(
                      t.substr(t.find("//") + 2).c_str()));
                }
                else if (t.find("/") != string::npos
                         && t.find("//") == string::npos)   // normal and texture coordinate index are
                  // contained in the string
                {
                  string components[3]; // Max 3 such components in Wavefront files
                  int numComponents = getTokens(t, '/', components);

                  int componentIdx = 0;

                  for (int compIdx = 0; compIdx < numComponents; ++compIdx) {
                    string component = components[compIdx];
                    switch (componentIdx) {
                      case 0:
                        v[idx - 1] = atoi(component.c_str());
                        break;
                      case 1:
                        textC.push_back(atoi(
                            component.c_str()));
                        break;
                      case 2:
                        n.push_back(atoi(component.c_str()));
                        break;
                    }
                    ++componentIdx;
                  }

                }

                else   // just the vertex index is contained in the string
                {
                  v[idx - 1] = atoi(t.c_str());
                }
              }
              ++idx;
            }
            facesVertexIndices.push_back(v);
            if (!n.empty())
              facesNormalIndices.push_back(n);
            if (!textC.empty())
              textureCoordsIndices.push_back(textC);
          }

        }
      }
      file.close();

      if (textureCoords.size() > 0) {
        this->correctDataVectors();
      }

      // Generate the data and delete the initial buffers
      this->loadVertexData();
      this->loadIndexData();
      this->loadNormalsData();
      this->loadTextureCoordsData();
      this->clear();

    }
    else
      throw Exception(
          "Could not open file " + string(SDL_GetBasePath())
          + fileLocation);
  }

}
