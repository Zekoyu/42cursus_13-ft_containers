/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 10-03-2022  by  `-'                        `-'                  */
/*   Updated: 10-03-2022 15:33 by                                             */
/*                                                                            */
/* ************************************************************************** */

class Base
{
	public:
		int value;
};


template <typename T>
class Derived1 : public Base
{
	public:
		T otherValue;
	
	void doThing() { otherValue = 0; }
};


int main()
{
	Derived1<int> pouet;

	pouet.doThing();

	Derived1<const int> pouet2;

	pouet = pouet2;
	pouet.doThing();
}
