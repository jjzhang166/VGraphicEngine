#include "../Samples.h"
#ifdef __SAMPLE_TEST_2__

int main()
{
	vg::core::mularray<vg::sl::SDepthTestNode> mma(8, 8, 4);
	mma.setSortInsertFunction(vg::sl::SortInsertFuncForSDepthTestNode);
	vg::sl::SDepthTestNode tempNode;
	tempNode.color = glm::vec4(0);
	int i, j;
	while (1)
	{
		std::cin >> tempNode.zwin;
		std::cin >> tempNode.color.a;
		std::cin >> i;
		std::cin >> j;
		mma.sortInsert(i, j, std::move(tempNode));

	}

}
#endif