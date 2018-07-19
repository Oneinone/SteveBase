#include <maths/Vector3.hpp>
#include <testSuite.hpp>

namespace SteveBase::Maths {
	go_bandit([]() {
		describe("Vector3 test:\n", [&] {
			describe("Operator arena:\n", [&] {
				describe("Plus\n", [&] {
					describe("Basic:\n", [&] {
						it("should return Vector3(1) for Vector3(0) + Vector3(1)", [] {
							AssertThat(
								Vector3(0) + Vector3(1),
								Is().EqualTo(Vector3(1))
							);
						});

						it("should return Vector3(1, 1) for Vector3(0, 0) + Vector3(1, 1)", [] {
							AssertThat(
								Vector3(0, 0) + Vector3(1, 1),
								Is().EqualTo(Vector3(1, 1))
							);
						});

						it("should return Vector3(1, 1, 1) for Vector3(0, 0) + Vector3(1, 1, 1)", [] {
							AssertThat(
								Vector3(0, 0, 0) + Vector3(1, 1, 1),
								Is().EqualTo(Vector3(1, 1, 1))
							);
						});
					});
				});
			});
		});
	});
}