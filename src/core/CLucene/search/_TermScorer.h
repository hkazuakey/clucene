/*------------------------------------------------------------------------------
* Copyright (C) 2003-2006 Ben van Klinken and the CLucene Team
* 
* Distributable under the terms of either the Apache License (Version 2.0) or 
* the GNU Lesser General Public License, as specified in the COPYING file.
------------------------------------------------------------------------------*/
#ifndef _lucene_search_TermScorer_
#define _lucene_search_TermScorer_


#include "Scorer.h"
#include "CLucene/index/Terms.h"
CL_CLASS_DEF(search,Similarity)
#include "SearchHeader.h"

CL_NS_DEF(search)
    
	class TermScorer: public Scorer {
	private:
		CL_NS(index)::TermDocs* termDocs;
		uint8_t* norms;
		Weight* weight;
		const float_t weightValue;
		int32_t _doc;

		int32_t docs[32];	  // buffered doc numbers
		int32_t freqs[32];	  // buffered term freqs
		int32_t pointer;
		int32_t pointerMax;

		float_t scoreCache[LUCENE_SCORE_CACHE_SIZE];
	public:

		//TermScorer takes TermDocs and delets it when TermScorer is cleaned up
		TermScorer(Weight* weight, CL_NS(index)::TermDocs* td, 
				Similarity* similarity, uint8_t* _norms);

		~TermScorer();

		int32_t doc() const { return _doc; }

		bool next();
		bool skipTo(int32_t target);

    /** Returns an explanation of the score for a document.
    * <br>When this method is used, the {@link #next()} method
    * and the {@link #score(HitCollector)} method should not be used.
    * @param doc The document number for the explanation.
    */
		void explain(int32_t doc, Explanation* ret);
		virtual TCHAR* toString();

		float_t score();
    };
CL_NS_END
#endif
