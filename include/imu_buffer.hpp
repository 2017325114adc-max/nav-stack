#pragma once 

#include "imu_types.hpp"

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <utility>

class ImuBuffer{
	public:

		explicit ImuBuffer(std::size_t capacity)
			: data_(std::make_unique<ImuSample[]>(capacity)),
			  capacity_(capacity),
			  size_(0)
		 {
		 }

		ImuBuffer(ImuBuffer&& other) noexcept
			: data_(std::move(other.data_)),
			  capacity_(other.capacity_),
			  size_(other.size_)
	        {
		        other.capacity_ = 0;
		        other.size_ = 0;
	        }

		 ImuBuffer(const ImuBuffer&) = delete;

		 ImuBuffer& operator = (const ImuBuffer&) = delete;

		 ImuBuffer& operator = (ImuBuffer&& other) noexcept{
			 
			 if(this != &other){
				 data_ = std::move(other.data_);
				 capacity_ = other.capacity_;
				 size_ = other.size_;

				 other.capacity_ = 0;
				 other.size_ = 0;
			 }

			 return *this;
		 }


		 bool pushBack(const ImuSample& sample)
		 {

		 	if(size_ >= capacity_)
			{
				return false;
			}

			data_[size_] = sample;

			size_++;

			return true;
		 }

		const ImuSample& at(std::size_t index) const{
			if(index >= size_){
				throw std::out_of_range("ImuBuffer Index out of range");
			}

			return data_[index];
		}

		std::size_t size() const noexcept{
			return size_;
		}

		std::size_t capacity() const noexcept{
			return capacity_;
		}

	private:

		std::unique_ptr<ImuSample[]> data_;
	
		std::size_t capacity_;

		std::size_t size_;

};
