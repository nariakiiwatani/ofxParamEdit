ofxParamEdit
============
by nariakiiwatani

Abstract------------
ofxParamEdit provides the SIMPLEST interface to edit values with GUI.
You don't have to keep ofxBaseGui instances in your code.
Only you have to do is passing normal variables (like int, float,,,) to ofxParamEdit (and keeping them alive).

Depend to...
------------
ofxGui

Usage
------------
see example/src/testApp.cpp

For ofxGui users
------------
convert your code like below...

from:

	ofxFloatSlider f;
	f.setup("float value", 0, -1, 1);
	f.draw();

to:

	float f = 0;
	ofxParamEdit edit;
	edit.addFloat("float value", f, -1, 1);
	edit.draw();

even after the change, doSomething(f) will remain the same. :)


Tips
------------
How to show two or more panels at the same time:

Create two or more ofxParamEdit instances.

How to edit a variable with multiple panel:

Add the variable twice simply.
(Because of ofxGui's spec, opposite view will not be updated.)


License
------------
built by nariakiiwatani  
facebook: nariakiiwatani  
twitter: @nariakiiwatani  
mail: nariakiiwatani@annolab.com  

----------------------------------------------------------

The MIT License

Copyright (c) 2012 nariakiiwatani and [anno lab]( http://www.annolab.com/ "anno lab")

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

----------------------------------------------------------
