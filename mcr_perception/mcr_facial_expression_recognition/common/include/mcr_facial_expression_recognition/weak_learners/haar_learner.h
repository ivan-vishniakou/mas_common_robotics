/*
 * This file is part of MultiBoost, a multi-class
 * AdaBoost learner/classifier
 *
 * Copyright (C) 2005-2006 Norman Casagrande
 * For informations write to nova77@gmail.com
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

/**
 * \file HaarLearner.h A generic interface for Haar-Like features.
 */

#ifndef __HAAR_LEARNER_H
#define __HAAR_LEARNER_H

#include <string>
#include <vector>
#include <iosfwd>

#include "utils/utils.cpp" // for rect

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

// forward declarations to save some includes
namespace nor_utils
{
	class StreamTokenizer;
	class Args;
}

namespace MultiBoost
{

// forward declarations to save some includes
	class HaarFeature;
	class HaarData;

	/**
	 * A generic interface to the learner based on Haar-like features.
	 * These features, first described in an AdaBoost environment by Viola and
	 * Jones in their 2001 paper (Robust Real-time Object Detection) are
	 * powerful way to treat with 1 or 2-dimensional data. This class
	 * it is \b not a learner itself, but must be extended among with another
	 * class that extend BaseLearner. For instance, the class
	 * HaarSingleStumpLearner extends SingleStumpLearner \b and HaarLearner.
	 *
	 * This class contains the generic operation for all the Haar-based
	 * learners.
	 * @date 16/12/2005
	 */
	class HaarLearner
	{
 	public:

		/**
		 * The constructor. Initializes the attributes belonging to all Haar-like based
		 * learners.
		 * @date 16/12/2005
		 */
		HaarLearner()
				: _pSelectedFeature(NULL),
				  _samplingType(ST_NO_SAMPLING),
				  _samplingVal(0)
		{
		}

		/**
		 * The destructor. Must be declared (virtual) for the proper destruction of
		 * the object.
		 */
		virtual ~HaarLearner()
		{
		}

		/**
		 * Declare Haar-learner-specific arguments.
		 * @remark It must be explicitly called by the derived class.
		 * @param args The Args class reference which can be used to declare
		 * additional arguments.
		 * @date 16/12/2005
		 */
		void declareArguments(nor_utils::Args& args);

		/**
		 * Set the arguments of the algorithm using the standard interface
		 * of the arguments. Call this to set the arguments asked by the user.
		 * @remark It must be explicitly called by the derived class.
		 * @param args The arguments defined by the user in the command line.
		 * @date 16/12/2005
		 */
		void initOptions(nor_utils::Args& args);

		/**
		 * Save the current object information needed for classification.
		 * @param outputStream The stream where the data will be saved
		 * @param numTabs The number of tabs before the tag. Useful for indentation
		 * @remark It must be explicitly called by the derived class.
		 * @see StumpLearner::save()
		 * @date 16/12/2005
		 */
		virtual void save(ofstream& outputStream, int numTabs = 0);

		/**
		 * Load the xml file that contains the serialized information
		 * needed for the classification and that belongs to this class.
		 * @remark It must be explicitly called by the derived class.
		 * @param st The stream tokenizer that returns tags and values as tokens
		 * @see save()
		 * @date 16/12/2005
		 */
		virtual void load(nor_utils::StreamTokenizer& st);

 	protected:

		/**
		 * The types of sampling techniques in the case not all the configurations are
		 * evaluated.
		 * @date 16/12/2005
		 */
		enum eSamplingType
		{
			ST_NO_SAMPLING,  //!< Default.
			ST_NUM,  //!<  A limited number per feature type, per iteration.
			ST_TIME  //!< A limited time per feature type, per iteration.
		};

		nor_utils::Rect _selectedConfig;  //!< The selected configuration of the feature.

		/**
		 * The selected feature type. This is a copy of the pointer to the loaded features types,
		 * and it is only used to access the Haar-computation function that belongs to the type.
		 * For instance, if during the current iteration a 2 blocs vertical feature is selected
		 * the pointer to this type of feature is copied here. During classification, this
		 * object is used to obtain the haar value computed with the Haar-like feature.
		 * @see HaarData::_loadedFeatures
		 * @see HaarFeature::getValue
		 * @date 17/12/2005
		 */
		HaarFeature* _pSelectedFeature;  //!< The selected feature type. A pointer to the

		/**
		 * The type of sampling.
		 * @see eSamplingType
		 * @date 17/12/2005
		 */
		eSamplingType _samplingType;

		/**
		 * The value associated the the sampling type.
		 *
		 * If \a _samplingType is ST_NUM, this variable holds the number of sampling
		 * configurations to be computed per feature, per boosting iteration.
		 *
		 * If \a _samplingType is ST_TIME, this variable holds the time limit for
		 * evaluating the configurations. This time is per configuration, per boosting
		 * iteration.
		 * @date 17/12/2005
		 */
		int _samplingVal;

	};

}  // end of namespace MultiBoost

#endif // __HAAR_LEARNER_H
