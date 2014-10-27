/*
*  SceneObject.h
*
*  Created on: 2014/10/19
*      Author: Dimitri Kourkoulis
*              http://dimitros.be
*     License: GNU LGPL
*/

#pragma once

#include <vector>
#include "Model.h"
#include <memory>
#include "EngineLog.h"
#include "Configuration.h"
#include "Image.h"
#include "BoundingBoxes.h"
#include "Vector3.h"
#include "Vector4.h"

using namespace std;

namespace small3d
{
	/**
	* A world object
	*/
	class SceneObject
	{
	private:
		shared_ptr<EngineLog> log;
		shared_ptr<Configuration> cfg;
		Model* model;
		bool animating;
		int frameDelay;
		int currentFrame;
		int framesWaited;
		int numFrames;
		shared_ptr<Image> texture;
		string name;
		shared_ptr<Vector4> colour;
		shared_ptr<Vector3> offset;
		shared_ptr<Vector3> rotation;
		shared_ptr<BoundingBoxes> boundingBoxes;

		void initPropVectors();

	public:

		/**
		* Constructor for object with texture
		* @param name The name of the object
		* @param modelPath The path to the file containing the object's model
		* @param cfg The game configuration file
		* @param log The game log
		* @param texturePath The path to the file containing the object's texture. If the object
		* 					  is animated, it has to be the path up to the name part of the model.
		* 					  The program will append an underscore, a 6-digit index number and the
		* 					  .obj suffix for each frame. (e.g. goatAnim will become goatAnim_000001.obj,
		* 					  goatAnim_000002.obj, etc.)
		* @param numFrames The number of frames, if the object is animated. A single animation
		* 					sequence is supported per object and the first frame is considered to
		* 					be the non-moving state.
		* @param boundingBoxesPath The path to the file containing the object's bounding boxes. If no such
		* 							path is given, the object cannot be checked for collision detection.
		*/
		SceneObject(const string &name, const string &modelPath,
			const shared_ptr<Configuration> cfg,
			const shared_ptr<EngineLog> log, const int &numFrames = 1, const string &texturePath = "",
			const string &boundingBoxesPath = "");

		/**
		* Destructor
		*/
		virtual ~SceneObject();

		/**
		* Get the object's model
		* @return The object's model
		*/
		Model& getModel() const;

		/**
		* Get the object's texture
		* @return The object's texture
		*/
		const shared_ptr<Image>& getTexture() const;

		/**
		* Get the name of the object
		* @return The name of the object
		*/
		const string getName();

		/**
		* Get the object's colour.
		* @return The object's colour.
		*/
		const shared_ptr<Vector4>& getColour();

		/**
		* Set the object's colour. This will only have an effect if the
		* object is not textured.
		* @param r The red component
		* @param g The green component
		* @param b The blue component
		* @param a The alpha component
		*/
		void setColour(const float &r, const float &g, const float &b, const float &a);


		/**
		* Get the offset of the object's position
		* @return The offset
		*/
		const shared_ptr<Vector3>& getOffset() const;

		/**
		* Set the offset of the object's position
		* @param x The offset's x coordinate
		* @param y The offset's y coordinate
		* @param z The offset's z coordinate
		*/
		void setOffset(const float &x, const float &y, const float &z);

		/**
		* Get the object's rotation
		* @return
		*/
		const shared_ptr<Vector3>& getRotation() const;

		/**
		* Set the object's rotation
		* @param x The orientation's x rotation
		* @param y The orientation's y rotation
		* @param z The orientation's z rotation
		*/
		void setRotation(const float &x, const float &y, const float &z);

		/**
		* Start animating the object
		*/
		void startAnimating();

		/**
		* Stop animating the object
		*/
		void stopAnimating();

		/**
		* Reset the animation sequence (go to first frame)
		*/
		void resetAnimation();

		/**
		* Set the animation speed
		* @param delay The delay between each animation frame, expressed in number of game frames
		*/
		void setFrameDelay(const int &delay);

		/**
		* Process animation (progress current frame if necessary)
		*/
		void animate();

		/**
		* Check if the object collides with a point of the given
		* coordinates
		*
		* @param	x	The x coordinate of the point
		* @param	y	The y coordinate of the point
		* @param	z	The z coordinate of the point
		*
		* @return	true if a collision is detected, false otherwise.
		*/

		bool collidesWithPoint(float x, float y, float z);

	};

}