#include <maths/Vector3.hpp>
#include <testSuite.hpp>

namespace SteveBase::Maths {
	go_bandit([]() {
		describe("Vector3 test:\n", [&] {
			describe("Operator arena:\n", [&] {
				describe("Minus\n", [&] {
					describe("Basic:\n", [&] {
						it("should return Vector3(-1) for Vector3(0) - Vector3(1)", [] {
							AssertThat(
								Vector3(0) - Vector3(1),
								Is().EqualTo(Vector3(-1))
							);
						});

						it("should return Vector3(0, 0) for Vector3(1, 1) - Vector3(1, 1)", [] {
							AssertThat(
								Vector3(1, 1) - Vector3(1, 1),
								Is().EqualTo(Vector3(0, 0))
							);
						});

						it("should return Vector3(1, 1, 1) for Vector3(6, 5, 4) - Vector3(5, 4, 3)", [] {
							AssertThat(
								Vector3(6, 5, 4) - Vector3(5, 4, 3),
								Is().EqualTo(Vector3(1, 1, 1))
							);
						});
					});
				});
			});
		});
	});
}