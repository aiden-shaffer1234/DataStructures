template <typename Object>
matrix<Object>::matrix( int rows, int cols ) : array{rows}
{
    for(int i = 0; i < rows; i++)
    {
        array[i].resize(cols);
    }
}

template <typename Object>
matrix<Object>::matrix( const Vector<Vector<Object>> & v ) : array{v}
{}

template <typename Object>
matrix<Object>::matrix( Vector<Vector<Object>> && v ) : array{std::move(v)}
{}

template <typename Object>
const Vector<Object> & matrix<Object>::operator[]( int row ) const
{
    return array[row];
}

template <typename Object>
Vector<Object> & matrix<Object>::operator[]( int row )
{
    return array[row];
}

template <typename Object>
int matrix<Object>::numrows( ) const
{
    return array.size();
}

template <typename Object>
int matrix<Object>::numcols( ) const
{
    if(numrows() == 0) return 0;
    
    return array[0].size();
}

template <typename Object>
void matrix<Object>::print(std::ostream &os)
{
    for (auto & thisRow : array)
    {
        os << thisRow << std::endl;
    }
}

template <typename Object>
void matrix<Object>::setValueAll(Object t)
{
    for (auto & thisRow : array)
    {
        for (auto & thisItem : thisRow)
        {
            thisItem = t;
        }
    }
}

template <typename Object>
std::ostream & operator<<(std::ostream &os, matrix<Object> &m)
{
    m.print(os);
    return os;
}

template <typename Object> // need;
matrix<Object> operator*(matrix<Object> & m1, matrix<Object> & m2)
{
    int rows = m1.numrows();
    int cols = m2.numcols();
    matrix<Object> result(rows, cols);

    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            result[i][j] = 0;
            for (int k = 0; k < m1.numcols(); k++) 
            {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }

    return result;
}