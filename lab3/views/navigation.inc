<?php include_once 'include/util.inc' ?>

<div id="nav">
	<ul>
		<li><?php echo isLoggedIn() ? '<a href="'. relativeUrl('logout') .'">Logout</a>' : '<a href="'. relativeUrl('login') .'">Login</a>'; ?></li>
		<li><?php echo isLoggedIn() ? '<a href="">My Profile</a>' : '<a href="'. relativeUrl('user/register') .'">Register</a>' ?></li>
		<li><?php echo '<a href="'. relativeUrl('index'). '">Home</a>' ?></li>
	</ul>
</div>