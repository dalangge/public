
#ifndef _TBUFFER_H_12345781234545
#define _TBUFFER_H_12345781234545

namespace Tool
{
	template<class T>
	class TBuff
	{
		static const size_t MIN_RESERVED = 256;

	public:
		TBuff() 
		{
			m_nReserved = MIN_RESERVED;
			m_nSize = 0;
			m_pData = new T[m_nReserved];
		}

		TBuff(size_t nReserved)
		{
			if (nReserved < MIN_RESERVED)
			{
				nReserved = MIN_RESERVED;
			}
			m_nReserved = nReserved;
			m_nSize = 0;
			m_pData = new T[m_nReserved];
		}

		~TBuff()
		{
			delete []m_pData;
		}

		size_t size() const 
		{
			return m_nSize;
		}

		T & operator[](size_t nPos) 
		{
			return m_pData[nPos];
		}

		const T & operator[](size_t nPos) const 
		{
			return m_pData[nPos];
		}

		void resize(size_t nSize)
		{
			size_t nReserved = m_nReserved;
			while (nReserved < nSize)
			{
				nReserved *= 2;
			}
			if (nReserved != m_nReserved)
			{
				m_nReserved = nReserved;
				T *pNewData = new T[m_nReserved];
				memcpy(pNewData, m_pData, m_nSize * sizeof(T));
				delete []m_pData;
				m_pData = pNewData;
			}
			m_nSize = nSize;
		}

		size_t append(const T *pData, size_t nLen)
		{
			size_t nSize = m_nSize;
			resize(m_nSize + nLen);
			memcpy(m_pData + nSize, pData, nLen * sizeof(T));
			return m_nSize;
		}

		size_t append(T t)
		{
			return append(&t, sizeof(t));
		}

		size_t append(const TBuff &buff)
		{
			return append(&buff[0], buff.size());
		}

		void swap(TBuff &buff)
		{
			T *pTmp = buff.m_pData;
			size_t tmp1 = buff.m_nSize;
			size_t tmp2 = buff.m_nReserved;

			buff.m_pData = m_pData;
			buff.m_nSize = m_nSize;
			buff.m_nReserved = m_nReserved;

			m_pData = pTmp;
			m_nSize = tmp1;
			m_nReserved = tmp2;
		}

		void clear()
		{
			m_nSize = 0;
		}

		void erase(size_t nPos, size_t nSize)
		{
			if (nPos >= m_nSize)
			{
				return;
			}
			if (nPos + nSize > m_nSize)
			{
				nSize = m_nSize - nPos;
			}
			memmove(m_pData + nPos, m_pData + nPos + nSize, (m_nSize - nSize - nPos) * sizeof(T));
			m_nSize -= nSize;
		}

	private:
		T *m_pData;
		size_t m_nReserved;
		size_t m_nSize;		
	};

}

#endif
