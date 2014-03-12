#pragma once

#include<cassert>
#include<vector>
#include<memory>
#include<utility>
using std::size_t;

class Matrix
{
public:
   typedef std::shared_ptr<Matrix>          pMatrix;
   typedef std::vector<double>              Vector;
   typedef std::shared_ptr<Vector>          pVector;
   typedef std::pair<size_t, size_t>        Point;//in form <row, col>
public:
   
   Matrix();

   Matrix(size_t width, size_t height);

   Matrix(const Matrix &other);

   ~Matrix();

   void Create(size_t width, size_t height);

   void Create(const Matrix &other);

   void Create(pVector array, size_t width);

public://public basic operation
   
   inline size_t GetWidth() const;

   inline size_t GetHeight() const;
   
   virtual inline double GetElement(size_t row, size_t col) const;

   virtual inline double GetElement(Point point) const;
   
   virtual inline void SetElement(size_t row, size_t col, double value);

   virtual inline void SetElement(Point point, double value);
   
   virtual inline pVector GetRow(size_t indexOfRow);

   virtual inline pVector GetColumn(size_t indexOfCol);

   virtual inline void SetRow(size_t indexOfRow, const pVector source);
   
   virtual inline void SetColumn(size_t indexOfCol, const pVector source);
/**
 * @name SetSubMatrix - replace the subset of this matrix with another
 * matrix.
 * @param point_begin - see the description of GetSubMatrix 
 * @param source -  the another matrix 
 * @return void
 */
   virtual inline void SetSubMatrix(Point point_begin, const pMatrix source);
/**
 * @name GetSubMatrix - get a subset matrix of this matrix. 
 * the region to be replaced is ( [point_begin, point_end) )
 * @param point_begin - starting position in this matrix, equal to top_left point
 * @param point_end - ending position in this matrix, equal to
 * button_right + 1.  
 * @return pMatrix - the result matrix
 */
   virtual inline pMatrix GetSubMatrix(Point point_begin, Point point_end);
public:

   bool IsSquared() const;

   bool IsSameSizeWith(pMatrix other) const;
/**
 * @name FilterByValid - 
 * @param window -  window 
 * @return pMatrix - filtered result
 */

   bool IsNonZeros();

   pMatrix FilterByValid(pMatrix window);

   pMatrix DotProduct(pMatrix other);

   Matrix& operator-=(const pMatrix other);

   pMatrix operator-(const pMatrix other);

   pMatrix operator+(const pMatrix other);

   pMatrix operator*(const pMatrix other);

   pMatrix operator^(const size_t index);

protected:
/**
 * @name GetData - return the pointer to the raw matrix data, as a
 * interface with Fortran
 * @return double*
 */
   double* GetData();

private://for the protection of raw data
   //data   
   std::vector<double>  data;	/**< raw data, arrayed in
				 * column-major order, for the
				 * compatibility with Fortran */
   size_t width;
   size_t height;
};

double Matrix::GetElement(size_t row, size_t col) const
{
   return data[col * height + row];
}

double Matrix::GetElement(Point point) const
{
   return data[point.second * height + point.first];
}
void Matrix::SetElement(size_t row, size_t col, double value)
{
   data[col * height + row] = value;
}

void Matrix::SetElement(Point point, double value)
{
   data[point.second * height + point.first] = value;
}

Matrix::pVector Matrix::GetRow(size_t indexOfRow)
{
   assert(indexOfRow < height);
   
   pVector target(new Vector(width));
   
   for(size_t col = 0; col < width; col++)
   {
      (*target)[col] = GetElement(indexOfRow, col);
   }
   return target;
}

void Matrix::SetRow(size_t indexOfRow, const pVector source)
{
   assert(indexOfRow < height);
   assert(source->size() == width);

   for(size_t col = 0; col < width; col++)
   {
      SetElement(indexOfRow, col,  (*source)[col]);
   }
}

Matrix::pVector Matrix::GetColumn(size_t indexOfCol)
{
   assert(indexOfCol < width);
   pVector target(new Vector(height));
   
   for(size_t row = 0; row < height; row++)
   {
      (*target)[row] = GetElement(row, indexOfCol);
   }
   return target;
}

void Matrix::SetColumn(size_t indexOfCol, const pVector source)
{
   assert(indexOfCol < GetWidth());
   assert(source->size() == GetHeight());

   for(size_t row = 0; row < GetHeight(); row++)
   {
      SetElement(row, indexOfCol, (*source)[row]);
   }
}

size_t Matrix::GetWidth() const
{
   return width;
}

size_t Matrix::GetHeight() const
{
   return height;
}

void Matrix::SetSubMatrix(Point point_begin, const pMatrix source)
{
   assert(point_begin.first + source->GetHeight() <= GetHeight());
   assert(point_begin.second + source->GetWidth() <= GetWidth());
   
   for(size_t row = 0; row < source->GetHeight(); row++)
   {
      for(size_t col = 0; col < source->GetWidth(); col++)
      {
	 SetElement(row + point_begin.first, col + point_begin.second, 
			 source->GetElement(row, col));
      }
   }
}

Matrix::pMatrix Matrix::GetSubMatrix(Point point_begin, Point point_end)
{
   assert(point_end.first > point_begin.first);
   assert(point_end.second > point_begin.first);
   assert(point_end.first <= GetHeight());
   assert(point_end.second <= GetWidth());

   pMatrix target(new Matrix(point_end.second - point_begin.second,
			     point_end.first - point_begin.first));
   
   for(size_t row = 0; row < target->GetHeight(); row++)
   {
      for(size_t col = 0; col < target->GetWidth(); col++)
      {
	 target->SetElement(row, col, 
			    GetElement(row + point_begin.first,
				       row + point_begin.second));
      }
   }
   return target;
}

Matrix::pMatrix operator+(Matrix::pMatrix me , const Matrix::pMatrix other);

Matrix::pMatrix operator^(Matrix::pMatrix me , const size_t index);

Matrix::pMatrix operator*(Matrix::pMatrix me,const Matrix::pMatrix other);

Matrix::pMatrix operator+=(Matrix::pMatrix me , const Matrix::pMatrix other);

//Matrix::pMatrix operator+=(Matrix::pMatrix me,const SymMatrix::pMatrix other);