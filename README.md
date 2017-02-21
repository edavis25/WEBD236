# WEBD-236 Persistent Lab

Basic question and answer forum in PHP using an MVC Framework. 4 WEBD-236 lab assignments add new functionality to the application.
- **Lab 2:** Implement ability to post and edit questions.
- **Lab 3:** Implement user profiles and login sessions.


---

**Note:** A templating language was provided by the course to be used when working with PHP in the views. The `renderTemplate()` function in `include/util.inc` processes the following syntax in the views:
- **{{** .. **}}** - Anything between double braces translates into a PHP echo statement.

  Ex: `{{ $string }}` - echo `$string` variable
- **[[** .. **]]** - Anything between double brackets is run as basic PHP code. These pretty much just replace normal tags (`<?php .. ?>`)

  Ex: `[[ $string = 'Hello world' ]]` - create `$string` variable
- **%%** .. **%%** - Double percents are `include` statements. Place string filepath from root directory between %%s.
  
  Ex: `%% include/util.inc %%` - includes the `util.inc` file
- **@@** .. **@@** - Resolves the application's base URL. Add string filepath from root directory between @@s.
 
  Ex: `<style href="@@css/style.css@@">` - resolve relative URLs for CSS import.
