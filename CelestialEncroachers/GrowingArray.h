#ifndef GROWING_ARRAY_HEADER
#define GROWING_ARRAY_HEADER

#include "CommonMacros.h"
#include <cstring>

namespace CommonUtilites
{
	template<class Type, class CountType = unsigned short>
	class GrowingArray
	{
	public:
		GrowingArray();
		GrowingArray(const int &aMaxCount, const int &aGrowthSize = 10, bool aSafeMode = true);
		GrowingArray(const GrowingArray &anArray);
		~GrowingArray();

		GrowingArray &operator=(const GrowingArray &anArray);

		void Init(const int &aMaxCount, const int &aGrowthSize = 10, bool aSafeMode = true);
		void ReInit(const int &aMaxCount, const int &aGrowthSize = 10, bool aSafeMode = true);

		inline Type &operator[](const int &anIndex) const;

		inline void Add(const Type &anObject);
		inline void Insert(const int &anIndex, Type &anObject);
		inline void Delete(const Type &anObject);
		inline void DeleteAt(const int &anIndex);
		inline void Remove(const Type &anObject);
		inline void RemoveAt(const int &anIndex);

		inline void DeleteAll();
		inline void RemoveAll();

		__forceinline int Count() const;

	private:
		inline void ReSize(const int &aSize);

		Type *myArray;
		CountType myCurrentCount;
		CountType myMaxCount;
		CountType myGrowthSize;

		bool myUseSafeMode;

	};

	template <class Type, class CountType>
	GrowingArray<Type, CountType>::GrowingArray()
	{
		myArray = nullptr;
		myCurrentCount = 0;
		myMaxCount = 0;
		myGrowthSize = 0;
		myUseSafeMode = false;
	}

	template <class Type, class CountType>
	GrowingArray<Type, CountType>::GrowingArray(const int &aMaxCount, const int &aGrowthSize, bool aSafeMode)
	{
		myArray = nullptr;
		myCurrentCount = 0;
		myUseSafeMode = aSafeMode;
		Init(aMaxCount, aGrowthSize, aSafeMode);
	}

	template <class Type, class CountType>
	GrowingArray<Type, CountType>::GrowingArray(const GrowingArray<Type, CountType> &anArray)
	{
		myArray = nullptr;
		*this = anArray;
	}

	template <class Type, class CountType>
	GrowingArray<Type, CountType>::~GrowingArray()
	{
		RemoveAll();
		if (myArray != nullptr)
		{
			ARRAY_SAFE_DELETE(myArray);
		}
		myArray = nullptr;
	}

	template <class Type, class CountType>
	void GrowingArray<Type, CountType>::Init(const int &aMaxCount, const int &aGrowthSize, bool aSafeMode)
	{
		myMaxCount = aMaxCount;
		myGrowthSize = aGrowthSize;
		myUseSafeMode = aSafeMode;
		myCurrentCount = 0;

		myArray = new Type[myMaxCount]();
	}

	template <class Type, class CountType>
	void GrowingArray<Type, CountType>::ReInit(const int &aMaxCount, const int &aGrowthSize, bool aSafeMode)
	{
		ARRAY_SAFE_DELETE(myArray);

		myMaxCount = aMaxCount;
		myGrowthSize = aGrowthSize;
		myUseSafeMode = aSafeMode;
		myCurrentCount = 0;

		myArray = new Type[myMaxCount]();
	}

	template <class Type, class CountType>
	GrowingArray<Type, CountType> &GrowingArray<Type, CountType>::operator=(const GrowingArray<Type, CountType> &anArray)
	{
		ReInit(anArray.myCurrentCount, anArray.myGrowthSize, anArray.myUseSafeMode);

		if (myUseSafeMode == true)
		{
			for (int i = 0; i < anArray.Count(); i++)
			{
				myArray[i] = anArray[i];
			}
		}
		else
		{
			memcpy(myArray, &anArray[0], anArray.Count() * sizeof(Type));
		}

		myCurrentCount = anArray.Count();

		return(*this);
	}

	template <class Type, class CountType>
	Type &GrowingArray<Type, CountType>::operator[](const int &anIndex) const
	{
		return(myArray[anIndex]);
	}

	template <class Type, class CountType>
	void GrowingArray<Type, CountType>::Add(const Type &anItem)
	{
		if (myCurrentCount == myMaxCount)
		{
			ReSize(myMaxCount + myGrowthSize);
		}

		myArray[myCurrentCount] = anItem;
		myCurrentCount++;
	}

	template <class Type, class CountType>
	void GrowingArray<Type, CountType>::Delete(const Type &anObject)
	{
		for (int i = 0; i < myCurrentCount; i++)
		{
			if (myArray[i] == anObject)
			{
				SAFE_DELETE(myArray[i]);
				myArray[i] = myArray[myCurrentCount - 1];
				myCurrentCount--;
				return;
			}
		}
	}

	template <class Type, class CountType>
	void GrowingArray<Type, CountType>::DeleteAt(const int &anIndex)
	{
		SAFE_DELETE(myArray[anIndex]);
		myArray[anIndex] = myArray[myCurrentCount - 1];
		myCurrentCount--;
	}

	template <class Type, class CountType>
	void GrowingArray<Type, CountType>::DeleteAll()
	{
		for (int i = 0; i < myCurrentCount; i++)
		{
			SAFE_DELETE(myArray[i]);
		}
		
		myCurrentCount = 0;
	}

	template <class Type, class CountType>
	void GrowingArray<Type, CountType>::Remove(const Type &anObject)
	{
		for (int i = 0; i < myCurrentCount; i++)
		{
			if (myArray[i] == anObject)
			{
				myArray[i] = myArray[myCurrentCount - 1];
				myCurrentCount--;
				return;
			}
		}
	}

	template <class Type, class CountType>
	void GrowingArray<Type, CountType>::RemoveAt(const int &anIndex)
	{
		myArray[anIndex] = myArray[myCurrentCount - 1];
		myCurrentCount--;
	}

	template <class Type, class CountType>
	void GrowingArray<Type, CountType>::RemoveAll()
	{
		myCurrentCount = 0;
	}

	template <class Type, class CountType>
	void GrowingArray<Type, CountType>::Insert(const int &anIndex, Type &anObject)
	{
		if (myCurrentCount == myMaxCount)
		{
			ReSize(myMaxCount + myGrowthSize);
		}

		for (int i = myCurrentCount - 1; i >= anIndex; i--)
		{
			myArray[i + 1] = myArray[i];
		}

		myArray[anIndex] = anObject;
		myCurrentCount++;
	}

	template <class Type, class CountType>
	int GrowingArray<Type, CountType>::Count() const
	{
		return(myCurrentCount);
	}

	template <class Type, class CountType>
	void GrowingArray<Type, CountType>::ReSize(const int &aSize)
	{
		Type *tempArray = new Type[aSize]();

		if (myUseSafeMode == true)
		{
			for (int i = 0; i < myCurrentCount; i++)
			{
				tempArray[i] = myArray[i];
			}
		}
		else
		{
			memcpy(tempArray, &myArray[0], myCurrentCount * sizeof(Type));
		}

		ARRAY_SAFE_DELETE(myArray);

		myMaxCount = aSize;
		myArray = tempArray;
	}
}
namespace CU = CommonUtilites;

#endif