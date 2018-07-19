#include <maths/Vector3.hpp>
#include <testSuite.hpp>

namespace SteveBase::Maths {
	go_bandit([]() {
		describe("Vector3 test:\n", [&] {
			describe("Operator arena:\n", [&] {
				describe("Plus\n", [&] {
					describe("Advanced\n", [&] {
						it("should return Vector3(1, 8) for Vector3(1) + Vector3(0, 8)", [] {
							AssertThat(
								Vector3(1) + Vector3(0, 8),
								Is().EqualTo(Vector3(1, 8))
							);
						});

						it("should return Vector3(-22, 8, 97) for Vector3(0, 8, 23) + Vector3(-22, 0, 74)", [] {
							AssertThat(
								Vector3(0, 8, 23) + Vector3(-22, 0, 74),
								Is().EqualTo(Vector3(-22, 8, 97))
							);
						});

						it("should return Vector3(0, 0, 0) for Vector3(7, -6, 23) + Vector3(-7, 6, -23)", [] {
							AssertThat(
								Vector3(7, -6, 23) + Vector3(-7, 6, -23),
								Is().EqualTo(Vector3(0, 0, 0))
							);
						});
					});
				});
			});
		});
	});
}