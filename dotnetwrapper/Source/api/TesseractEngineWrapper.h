/**
Copyright 2011, Cong Nguyen

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
**/

#pragma once

#include "Configuration.h"
#include "..\api\baseapi.h"
#include "CommonStructureWrapper.h"
#include "Word.h"
#include "DocumentLayout.h"

BEGIN_NAMSPACE

USING_COMMON_SYSTEM

USING_TESSERACT

USING_TESSERACT_ENGINE_WRAPPER

__gc public class TesseractProcessor
{	
private:
	String* _dataPath;
	String* _lang;
	int _ocrEngineMode;

private:
	bool _doMonitor;

public:	
	__property bool get_DoMonitor()
	{
		return _doMonitor;
	}

	__property void set_DoMonitor(bool doMonitor)
	{
		_doMonitor = doMonitor;
	}
	
private:
	System::IntPtr _apiInstance;
private:
	__property TessBaseAPI* get_EngineAPI()
	{
		if (_apiInstance == null)
		return null;

		TessBaseAPI* api = (TessBaseAPI*)_apiInstance.ToPointer();

		return api;
	}

public:	
	TesseractProcessor();
	~TesseractProcessor();

public:
	String* GetTesseractEngineVersion();

	bool Init();
	bool Init(String* dataPath, String* lang, int ocrEngineMode);

	void Clear();
	void ClearResults();
	void ClearAdaptiveClassifier();

	void End();

public:
	bool GetBoolVariable(System::String* name, bool __gc* value);
	bool GetIntVariable(System::String* name, int __gc* value);
	bool GetDoubleVariable(System::String* name, double __gc* value);
	System::String* GetStringVariable(System::String* name);

	bool SetVariable(System::String* nam, System::String* value);

private:
	void InitializeWorkingSpace();
	void InitializeEngineAPI();

	void InternalFinally();

public:
	String* Recognize(String* filePath);
	String* Recognize(System::Drawing::Image* image);
private:
	String* Process(Pix* pix);
	String* Process(TessBaseAPI* api, Pix* pix);

public:
	bool InitForAnalysePage();
	bool SetPageSegMode(ePageSegMode psm);

	DocumentLayout* AnalyseLayout(System::Drawing::Image* image);
private:
	DocumentLayout* AnalyseLayout(Pix* pix);
	DocumentLayout* AnalyseLayout(TessBaseAPI* api, Pix* pix);
};

END_NAMESPACE