template <typename T>
HashTable<T>::HashTable(size_t size): currentSize{0}
{
  long n;

  if(size < 1)  n = default_capacity;
  else          n = prime_below(size);
  theLists.resize(n); //check
  std::cout << n << std::endl;
}  

template <typename T>
HashTable<T>::~HashTable(){
  makeEmpty();
}

// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename T>
unsigned long HashTable<T>::prime_below(long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename T>
void HashTable<T>::setPrimes(std::vector<long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

template <typename T>
size_t HashTable<T>::myhash(const T &x) {
	static std::hash<T> hf;
	return hf(x) % theLists.size();
}

template <typename T>
void HashTable<T>::makeEmpty() {
	for (auto & thisList : theLists) {
		thisList.clear();	
	}
}

template <typename T>
bool HashTable<T>::contains(const T & x) {
	auto & whichList = theLists[myhash(x)];
	return find(begin(whichList), end(whichList), x) != end(whichList);
}

template <typename T>
bool HashTable<T>::remove(const T & x) {
	auto & whichList = theLists[myhash(x)];
	auto itr = find(begin(whichList), end(whichList), x);

	if (itr == end(whichList))
		return false;
	whichList.erase(itr);
	--currentSize;
	return true;
}


template <typename T>
bool HashTable<T>::insert(const T & x) {
	auto & whichList = theLists[myhash(x)];
	if (find(begin(whichList), end(whichList), x) != end(whichList))
		return false;

	whichList.push_back(x);

	//  rehash, see Section 5.5
	if (++currentSize > theLists.size())
		rehash();

	return true;
}

template <typename T>
bool HashTable<T>::insert(T && x) {
	auto & whichList = theLists[myhash(x)];
	if (find(begin(whichList), end(whichList), x) != end(whichList))
		return false;

	whichList.push_back(std::move(x));

	//  rehash, see Section 5.5
	if (++currentSize > theLists.size())
		rehash();

	return true;
}

template <typename T>
void HashTable<T>::rehash() {
	std::vector<std::list<T>> oldLists = theLists;

	// create new double-sized, empty table
	theLists.resize(prime_below(2 * theLists.size()));
	for (auto & thisList: theLists)
		thisList.clear();

	// copy table over
	currentSize = 0;
	for (auto & thisList : oldLists)
		for (auto & x : thisList)
			insert(std::move(x));
}

template <typename T>
void HashTable<T>::clear(){
  makeEmpty();
  currentSize = 0;
}

template <typename T>
size_t HashTable<T>::size()
{
  return currentSize;
}

template <typename T>
bool HashTable<T>::load(const char *filename)
{
  std::ifstream in;
  in.open(filename);


  // Check if the file was opened successfully
  if (!in.is_open()) {
    return false;
  }

  // Read the contents of the file
  T line;
  while (in >> line) {
    insert(line);
  }

  // Close the file
  in.close();
  return true;
}

template <typename T>
void HashTable<T>::dump()
{
  int count = 0;
  for (auto & thisList : theLists)
  {
    std::cout << "v[" << count++ << "] : "; 
    for (auto & x : thisList)
    {
        std::cout << x  << "\t";
    }
    std::cout << std::endl;
  }
}

template <typename T>
bool HashTable<T>::write_to_file(const char *filename){
  std::ofstream out;
  out.open(filename);

  if(!out.is_open())
  {
    return false;
  }

  for (auto & thisList :theLists)
  {
    for (auto & x : thisList)
    {
      out << x << std::endl;
    }
  }

  out.close();
  return true;
}
