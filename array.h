#pragma once

#include <vector>

template<class T>
class slice_array
{
public:
	slice_array()
		: data(nullptr)
	{

	}

	slice_array(const T* ptr_, size_t cap_)
		: data(std::make_shared<std::vector<T>>(cap_))
	{
		for (size_t i = 0; i < cap_; i++)
		{
			(*data)[i] = ptr_[i];
		}
	}

	T& operator[](size_t i) const
	{
		return (*data)[i];
	}

	void append(size_t begin, std::initializer_list<T> array_)
	{
		(*data).resize(begin + array_.size());
		int i = begin;
		for (auto elem = array_.begin(); elem != array_.end(); elem++, i++)
		{
			(*data)[i] = *elem;
		}
	}

	void append(size_t begin, const slice_array& array_, size_t begin_, size_t end_)
	{
		(*data).resize(begin + end_ - begin_);
		int i = begin;
		if (*this != array_)
		{
			for (size_t k = begin_; k < end_; k++, i++)
			{
				(*data)[i] = array_[k];
			}
		}
		else
		{
			// 自己加自己，为了防止脏数据，先拷贝下
			std::vector<T*> temp(end_ - begin_);
			int j = 0;
			for (size_t k = begin_; k < end_; k++, j++)
			{
				temp[j] = &array_[k];
			}
			for (size_t k = 0; k < temp.size(); k++, i++)
			{
				(*data)[i] = *(temp[k]);
			}
		}
	}

	void remove(size_t index)
	{
		if (index + 1 != data->size())
		{
			(*data)[index] = (*data)[data->size() - 1];
		}
		data->resize(data->size() - 1);
	}

	void remove(size_t begin_, size_t end_)
	{
		int i = begin_;
		int j = int(data->size() - 1);
		for (; i < int(end_) && j >= int(end_); i++, j--)
		{
			(*data)[i] = (*data)[j];
		}
		data->resize(data->size() - (end_ - begin_));
	}

	bool operator==(const slice_array& array_) const
	{
		return data.get() == array_.data.get();
	}

	bool operator!=(const slice_array& array_) const
	{
		return data.get() != array_.data.get();
	}

private:
	std::shared_ptr<std::vector<T>> data;
};