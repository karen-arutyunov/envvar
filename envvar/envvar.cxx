#include <string>
#include <cassert>
#include <iostream>

#include <libbutl/utility.mxx>
#include <libbutl/process.mxx>
#include <libbutl/optional.mxx>

using namespace std;
using namespace butl;

int main (int argc, char* argv[])
{
  using butl::optional;
  using butl::getenv;

  assert (argc < 3);

  if (argc == 2)
  {
    assert (string (argv[1]) == "-c");

    optional<string> v (getenv ("BUILD2_VAR_OVR"));
    cout << "BUILD2_VAR_OVR=";

    if (v)
      cout << "'" << *v << "'" << endl;
    else
      cout << "<none>" << endl;

    return 0;
  }

  string vars (
    "!config.abc.xyz = {A B C}\n"
    "!config.xyz.abc = ('X\"Y\"Z)\n");

  setenv ("BUILD2_VAR_OVR", vars);

  process_run (0, 1, 2, argv[0], "-c");
}
