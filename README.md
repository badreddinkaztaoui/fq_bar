# ft_bar

**A simple and lightweight system status monitoring tool.**

**Installation:**

***Clone the repo***
```bash
  git clone [https://github.com/badreddinkaztaou/ft_bar](https://github.com/badreddinkaztaoui/ft_bar)
  cd ft_bar
```
***Compile the code***
```bash
  cc -Wall -Wextra -Werror -o ft_bar ft_bar.c -lX11 -lXrandr
  mv ft_bar /usr/local/bin/
```
***Update your .xinitrc file to run the code when dwn runs***
```bash
  // add this line to you .xinitrc file
  ft_bar &
```
**Example output:**
```bash
  RAM: 2.3/4.0 GB | CPU: 25.6% | 12:34 (01-01-2024) | hostname release
```
**Configuration:**

    Time Format: Modify the TIME_FORMAT macro in ft_bar.c to customize the time display format.
    Update Interval: Adjust the sleep(1) line in ft_bar.c to change the update frequency.

Customization:

    Metrics: Add new metrics by creating functions and including them in the snprintf statement in the main function.
    Formatting: Modify the output formatting by adjusting the snprintf statement and the string formatting within the functions.
