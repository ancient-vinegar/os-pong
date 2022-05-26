#include "VertexBufferElement.h"

#include <glad/glad.h>

unsigned int rendering::VertexBufferElement::GetSizeOfType(unsigned int type)
{
	switch (type) {
	case GL_FLOAT:				return sizeof GLfloat;
	case GL_UNSIGNED_INT:		return sizeof GLuint;
	case GL_UNSIGNED_BYTE:		return sizeof GLubyte;
	}
	// TODO: Log a type failure.
	return 0;
}
