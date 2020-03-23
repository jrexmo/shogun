/*
 * This software is distributed under BSD 3-clause license (see LICENSE file).
 *
 * Authors: Gil Hoben
 */

#include <unsupported/Eigen/CXX11/Tensor>

namespace shogun::graph::op {
	template <typename T>
	void multiply_kernel_implementation_sse2(
	    void* input1, void* input2, void* output, const size_t size);

	template <typename T>
	void multiply_kernel_implementation_sse2(
	    void* input1, void* input2, void* output, const size_t size)
	{
		Eigen::TensorMap<Eigen::Tensor<T, 1>> A(static_cast<T*>(input1), size);
		Eigen::TensorMap<Eigen::Tensor<T, 1>> B(static_cast<T*>(input2), size);
		Eigen::TensorMap<Eigen::Tensor<T, 1>> Out(static_cast<T*>(output), size);

		Out.device(Eigen::DefaultDevice{}) = A * B;
	}

	template <>
	void multiply_kernel_implementation_sse2<bool>(
	    void* input1, void* input2, void* output, const size_t size)
	{
		std::transform(
		    static_cast<const bool*>(input1),
		    static_cast<const bool*>(input1) + size,
		    static_cast<const bool*>(input2), static_cast<bool*>(output),
		    std::multiplies<bool>());
	}

	template void multiply_kernel_implementation_sse2<int8_t>(void*, void*, void*, const size_t);
	template void multiply_kernel_implementation_sse2<int16_t>(void*, void*, void*, const size_t);
	template void multiply_kernel_implementation_sse2<int32_t>(void*, void*, void*, const size_t);
	template void multiply_kernel_implementation_sse2<int64_t>(void*, void*, void*, const size_t);
	template void multiply_kernel_implementation_sse2<uint8_t>(void*, void*, void*, const size_t);
	template void multiply_kernel_implementation_sse2<uint16_t>(void*, void*, void*, const size_t);
	template void multiply_kernel_implementation_sse2<uint32_t>(void*, void*, void*, const size_t);
	template void multiply_kernel_implementation_sse2<uint64_t>(void*, void*, void*, const size_t);
	template void multiply_kernel_implementation_sse2<float>(void*, void*, void*, const size_t);
	template void multiply_kernel_implementation_sse2<double>(void*, void*, void*, const size_t);
}