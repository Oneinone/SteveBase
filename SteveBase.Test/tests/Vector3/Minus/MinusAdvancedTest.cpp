#include <maths/Vector3.hpp>
#include <testSuite.hpp>

namespace SteveBase::Maths {
	go_bandit([]() {
		describe("Vector3 test:\n", [&] {
			describe("Operator arena:\n", [&] {
				describe("Minus\n", [&] {
					describe("Advanced\n", [&] {
						it("should return Vector3(1, 8, 7) for Vector3(66, 28, 13) - Vector3(65, 20, 6)", [] {
							AssertThat(
								Vector3(66, 28, 13) - Vector3(65, 20, 6),
								Is().EqualTo(Vector3(1, 8, 7))
							);
						});

						it("should return Vector3(987) for Vector3(1038, -574, -129) - Vector3(51, 574, 129)", [] {
							AssertThat(
								Vector3(1038, 574, 129) - Vector3(51, 574, 129),
								Is().EqualTo(Vector3(987))
							);
						});

						it("should return Vector3(1962, 226, 2474) for Vector3(981, 113, 1237) - Vector3(-981, -113, -1237)", [] {
							AssertThat(
								Vector3(981, 113, 1237) - Vector3(-981, -113, -1237),
								Is().EqualTo(Vector3(1962, 226, 2474))
							);
						});
					});
				});
			});
		});
	});
}