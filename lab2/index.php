<?php
include_once 'include/util.inc';

// This is the "home page", which redirects to the index controller
// (controllers/index.inc) get_index() function, which may redirect to
// the actual home page controller/function...
redirect("index");
