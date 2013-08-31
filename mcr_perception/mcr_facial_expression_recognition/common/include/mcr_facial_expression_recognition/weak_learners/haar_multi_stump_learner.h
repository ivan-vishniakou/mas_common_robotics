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
 * \file HaarMultiStumpLearner.h A learner that uses the Haar-like features for
 * input and the MultiStumpLearner for training.
 * @date 17/12/2005
 */

#ifndef __HAAR_MULTI_STUMP_LEARNER_H
#define __HAAR_MULTI_STUMP_LEARNER_H

#include "weak_learners/haar_learner.cpp"
#include "weak_learners/multi_stump_learner.cpp"

#include "utils/utils.cpp"

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

namespace MultiBoost
{

	class HaarData;

	/**
	 * A learner that uses the Haar-like features for input and the MultiStumpLearner
	 * for training.
	 * @see HaarLearner
	 * @see MultiStumpLearner
	 * @date 17/12/2005
	 */
	class HaarMultiStumpLearner : public HaarLearner, public MultiStumpLearner
	{
 	public:

		/**
		 * The destructor. Must be declared (virtual) for the proper destruction of
		 * the object.
		 */
		virtual ~HaarMultiStumpLearner()
		{
		}

		/**
		 * Declare weak-learner-specific arguments.
		 * These arguments will be added to the list of arguments under
		 * the group specific of the weak learner. It is called
		 * automatically in main, when the list of arguments is built up.
		 * Use this method to declare the arguments that belongs to
		 * the weak learner only.
		 * @param args The Args class reference which can be used to declare
		 * additional arguments.
		 * @date 28/11/2005
		 */
		virtual void declareArguments(nor_utils::Args& args);

		/**
		 * Set the arguments of the algorithm using the standard interface
		 * of the arguments. Call this to set the arguments asked by the user.
		 * @param args The arguments defined by the user in the command line.
		 * @date 14/11/2005
		 */
		virtual void initOptions(nor_utils::Args& args);

		/**
		 * Return {+1, -1} for the given class and value using the learned classifier.
		 * @param pData The pointer to the data
		 * @param idx The index of the example to classify
		 * @param classIdx The index of the class
		 * @remark This override classify of StumpLearner, as the data must be
		 * transformed to haar-like feature space.
		 * @remark Passing the data and the index to the example is not nice at all.
		 * This will soon be replace with the passing of the example itself in some
		 * form (probably a structure to the example).
		 * @return +1 if the classifier thinks that \a val belongs to class
		 * \a classIdx, -1 if it does not and 0 if it abstain
		 * @date 13/11/2005
		 */
		virtual double classify(InputData* pData, int idx, int classIdx);

		/**
		 * Returns itself as object.
		 * @remark It uses the trick described in
		 * http://www.parashift.com/c++-faq-lite/serialization.html#faq-36.8
		 * for the auto-registering classes.
		 * @date 14/11/2005
		 */
		virtual BaseLearner* create()
		{
			return new HaarMultiStumpLearner();
		}

		/**
		 * Creates an InputData object that it is good for the
		 * weak learner. Overridden to return HaarData.
		 * @see InputData
		 * @see BaseLearner::createInputData()
		 * @see SortedData
		 * @warning The object \b must be destroyed by the caller.
		 * @date 21/11/2005
		 */
		virtual InputData* createInputData();

		/**
		 * Run the learner to build the classifier on the given data.
		 * @param pData The pointer to the data
		 * @see SingleStumpLearner::run
		 * @date 11/11/2005
		 */
		virtual void run(InputData* pData);

		/**
		 * Save the current object information needed for classification.
		 * @param outputStream The stream where the data will be saved
		 * @param numTabs The number of tabs before the tag. Useful for indentation
		 * @remark To fully save the object it is \b very \b important to call
		 * also the super-class method.
		 * @see StumpLearner::save()
		 * @date 13/11/2005
		 */
		virtual void save(ofstream& outputStream, int numTabs = 0);

		/**
		 * Load the xml file that contains the serialized information
		 * needed for the classification and that belongs to this class.
		 * @param st The stream tokenizer that returns tags and values as tokens
		 * @see save()
		 * @date 13/11/2005
		 */
		virtual void load(nor_utils::StreamTokenizer& st);

	};

}  // end of namespace MultiBoost

#endif // __HAAR_MULTI_STUMP_LEARNER_H
