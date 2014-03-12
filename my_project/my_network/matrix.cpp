
#include "matrix.hpp"
#include"sym_matrix.hpp"


Matrix::Matrix()
   :width(0), height(0)
{
}

Matrix::Matrix(size_t width, size_t height)
{
   Create(width, height);
}

Matrix::Matrix(const Matrix &other)
{
   Create(other);
}

Matrix::~Matrix()
{
}

bool Matrix::IsSquared() const
{
   if(width == height)
      return true;
   else
      return false;
}

void Matrix::Create(size_t width, size_t height)
{
   this->width = width;
   this->height = height;
   data.assign(width * height, 0.0);
}

void Matrix::Create(const Matrix &other)
{
   this->width = other.width;
   this->height = other.height;
   data.assign(other.data.begin(), other.data.end());
}

double* Matrix::GetData()
{
   return data.data();
}

void Matrix::Create(pVector array, size_t width)
{
   this->width = width;
   this->height = array->size() / width;
   data.assign(array->begin(), array->end());
}

bool Matrix::IsSameSizeWith(pMatrix other) const
{
   if(this->width == other->GetWidth() &&
      this->height == other->GetHeight())
      return true;
   else
      return false;
}

Matrix& Matrix::operator-=(const pMatrix other)
{
   assert(IsSameSizeWith(other));

   for(size_t row = 0; row < GetHeight(); row++)
   {
      for(size_t col = 0; col < GetWidth(); col++)
      {
	 SetElement(row, col, GetElement(row, col) - other->GetElement(row, col));
      }
   }
   return *this;
}

Matrix::pMatrix Matrix::operator-(const pMatrix other)
{
   assert(IsSameSizeWith(other));
   
   pMatrix result(new Matrix(GetWidth(), GetHeight()));

   for(size_t row = 0; row < GetHeight(); row++)
   {
      for(size_t col = 0; col < GetWidth(); col++)
      {
	 result->SetElement(row, col, 
			    GetElement(row, col) - other->GetElement(row, col));
      }
   }
   return result;
}

Matrix::pMatrix operator+=(Matrix::pMatrix me,const Matrix::pMatrix other)
{
   assert(me->IsSameSizeWith(other));
   for(size_t row = 0; row < me->GetHeight(); row++)
   {
      for(size_t col = 0; col < me->GetWidth(); col++)
      {
	 me->SetElement(row, col, me->GetElement(row, col) + other->GetElement(row, col));
      }
   }
   return me;
}

//Matrix::pMatrix operator+=(Matrix::pMatrix me,const SymMatrix::pMatrix other)
//{
//   assert(me->IsSameSizeWith(other));
//   for(size_t row = 0; row < me->GetHeight(); row++)
//   {
//      for(size_t col = 0; col < me->GetWidth(); col++)
//      {
//	 me->SetElement(row, col, me->GetElement(row, col) + other->GetElement(row, col));
//      }
//   }
//   return me;
//}

//Matrix::pMatrix Matrix::operator+(const pMatrix other)
//{
//	assert(IsSameSizeWith(other));
//   
//   pMatrix result(new Matrix(GetWidth(), GetHeight()));
//
//   for(size_t row = 0; row < GetHeight(); row++)
//   {
//      for(size_t col = 0; col < GetWidth(); col++)
//      {
//	 result->SetElement(row, col, 
//			    this->GetElement(row, col) + other->GetElement(row, col));
//      }
//   }
//   return result;
//}
Matrix::pMatrix operator+(Matrix::pMatrix me,const Matrix::pMatrix other)
{
	assert(me->IsSameSizeWith(other));
   
   Matrix::pMatrix result(new Matrix(me->GetWidth(), me->GetHeight()));

   for(size_t row = 0; row < me->GetHeight(); row++)
   {
      for(size_t col = 0; col < me->GetWidth(); col++)
      {
	 result->SetElement(row, col, 
			    me->GetElement(row, col) + other->GetElement(row, col));
      }
   }
   return result;
}

//Matrix::pMatrix Matrix::operator*(const pMatrix other)
//{
//	assert(this->GetWidth() == other->GetHeight());
//
//	pMatrix result(new Matrix(this->GetHeight(), other->GetWidth()));
//
//	for(size_t row = 0; row < result->GetHeight(); row++)
//	{
//		for(size_t col = 0;col < result->GetWidth();col++)
//		{
//			double tempsum = 0.0;
//			for(size_t k = 0; k < this->GetWidth();k++)
//			{
//				tempsum += this->GetElement(row,k)*other->GetElement(k,col);
//			}
//			result->SetElement(row,col,tempsum);
//		}
//	}
//	return result;
//}

Matrix::pMatrix operator*(Matrix::pMatrix me,const Matrix::pMatrix other)
{
	assert(me->GetWidth() == other->GetHeight());

	Matrix::pMatrix result(new Matrix(me->GetHeight(), other->GetWidth()));

	for(size_t row = 0; row < result->GetHeight(); row++)
	{
		for(size_t col = 0;col < result->GetWidth();col++)
		{
			double tempsum = 0.0;
			for(size_t k = 0; k < me->GetWidth();k++)
			{
				tempsum += me->GetElement(row,k)*other->GetElement(k,col);
			}
			result->SetElement(row,col,tempsum);
		}
	}
	return result;
}

//Matrix::pMatrix Matrix::operator^(const size_t index)
//{
//	auto size = this->GetWidth();
//	pMatrix result(new Matrix(size,size));
//	for(size_t i = 0;i < size;i++)
//	{
//			result->SetElement(i,i,1);
//	}
//
//	for(size_t k =0; k < index; k++)
//	{
//		result = (*this) * (result);
//	}
//	return result;
//}

Matrix::pMatrix operator^(Matrix::pMatrix me , const size_t index)
{
	auto size=me->GetWidth();
	Matrix::pMatrix result(new Matrix(me->GetWidth(), me->GetHeight()));
	for(size_t i = 0;i < size;i++)
	{
		result->SetElement(i,i,1);
	}

	for(size_t k =0; k < index; k++)
	{
		result = result * me;
	}
	return result;
}


bool Matrix::IsNonZeros()
{
	auto size = this->GetWidth();
	for(size_t i = 0; i < size; i++)
	{
		for(size_t j = 0;j < size;j++)
		{
			if(abs(this->GetElement(i,j) - 0) <1.0e-3)
				return false;
		}
	}
	return true;
}


Matrix::pMatrix Matrix::DotProduct(pMatrix other)
{
   assert(IsSameSizeWith(other));

   pMatrix result(new Matrix(GetWidth(), GetHeight()));
   
   for(size_t row = 0; row < GetHeight(); row++)
   {
      for(size_t col = 0; col < GetWidth(); col++)
      {
	 result->SetElement(row, col, 
			    GetElement(row, col) * other->GetElement(row, col));
      }
   }
   return result;
}

Matrix::pMatrix Matrix::FilterByValid(pMatrix window)
{
   assert(window->GetWidth() <= GetWidth() &&
	  window->GetHeight() <= GetHeight());

   pMatrix result(new Matrix(GetWidth() - window->GetWidth() + 1,
			     GetHeight() - window->GetHeight() + 1));
   
   for(size_t row = 0; row < result->GetHeight(); row++)
   {
      for(size_t col = 0; col < result->GetWidth(); col++)
      {
	 double sum = 0;
	 for(size_t row_w = 0; row_w < window->GetHeight(); row_w++)
	 {
	    for(size_t col_w = 0; col_w < window->GetWidth(); col_w++)
	    {
	       sum += GetElement(row + row_w, col + col_w);
	    }
	 }
	 result->SetElement(row, col, sum);
      }
   }
   return result;
}
