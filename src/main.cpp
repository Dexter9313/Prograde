/*
    Copyright (C) 2018 Florian Cabot <florian.cabot@hotmail.fr>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

//#include "exceptions/Exceptions.hpp"
#include <iostream>

#include "graphics/LauncherWindow.hpp"
#include "graphics/MainWindow.hpp"

int main(int argc, char* argv[])
{
	// BEGIN_EXCEPTIONS

	// std::cout << "pname:" << Exceptions::getProgramName() << std::endl;

	Urho3D::ParseArguments(argc, argv);
	// Urho3D::SharedPtr<Urho3D::Context> context(new Urho3D::Context());

	// dynamic allocation for memory management,
	// there is no need to keep the launcher's data in memory while simulation
	// is running
	auto lWindow = new LauncherWindow(new Urho3D::Context());

	lWindow->Run();

	if(!lWindow->returned.launch)
	{
		return 0;
	}

	auto copy = new LauncherWindow::LauncherReturned;
	*copy     = lWindow->returned;
	delete lWindow; // save some memory

	MainWindow mWindow(new Urho3D::Context(), *copy);

	delete copy; // save more memory

	mWindow.Run();
	// END_EXCEPTIONS

	return 0;
}
