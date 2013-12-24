// Copyright (c) 2012 AlterEgo Studios
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#define QGLITTER_DECLARE_PUBLIC(Class) \
	inline Class* qglitter_q_func() { return static_cast<Class *>(qglitter_q_ptr); } \
	inline const Class* qglitter_q_func() const { return static_cast<const Class *>(qglitter_q_ptr); } \
	friend class Class;

#define QGLITTER_DECLARE_PRIVATE(Class) \
	inline Class##Private* qglitter_d_func() { return reinterpret_cast<Class##Private *>(qglitter_d_ptr); } \
	inline const Class##Private* qglitter_d_func() const { return reinterpret_cast<const Class##Private *>(qglitter_d_ptr); } \
	friend class Class##Private;

#define QGLITTER_D(Class) Class##Private * const d = qglitter_d_func()
#define QGLITTER_Q(Class) Class * const q = qglitter_q_func()

#define QGLITTER_DISABLE_COPY(Class) \
	Class(const Class &); \
	Class &operator=(const Class &);

class QGlitterObject;

class QGlitterObjectData
{
public:
	QGlitterObjectData() : qglitter_q_ptr(0) {}
	virtual ~QGlitterObjectData() {}

	QGlitterObject *qglitter_q_ptr;
};

class QGlitterObject
{
public:
	virtual ~QGlitterObject() { if (qglitter_d_ptr) { delete qglitter_d_ptr; qglitter_d_ptr = 0; } }

protected:
	QGlitterObject(QGlitterObjectData *d_ptr) : qglitter_d_ptr(d_ptr) { if (qglitter_d_ptr) { qglitter_d_ptr->qglitter_q_ptr = this; } }

	QGlitterObjectData *qglitter_d_ptr;
};
