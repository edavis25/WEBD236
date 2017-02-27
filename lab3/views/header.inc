<!DOCTYPE html>
<html>
	<head>
		<link rel="stylesheet" href="@@css/style.css@@" />
		
		<title>{{ $title }}</title>
	</head>
	<body>
		<!-- Page wrapper -->
		<div id="content-wrapper">
			
			<!-- Navigation bar -->
			<div id="nav">
				<ul>
					
					[[if (isLoggedIn()) : ]]
						<li><a href="@@logout@@">Logout</a></li>
						<li><a href="">My Profile</a></li>
					[[ else : ]]
						<li><a href="@@login@@">Login</a></li>
						<li><a href="@@user/register@@">Register</a></li>	
					[[ endif; ]]
					
					<!-- Home link always present -->
					<li><a href="@@index@@">Home</a></li>
				</ul>
			</div>
			
			<!-- User greeting -->
			<div id="greeting">
				[[ if (isLoggedIn()) : ]]
					{{ "Welcome, " . safeParam($_SESSION, 'FirstName', false) ." ". safeParam($_SESSION, 'LastName', false) ."!" }}
				[[ endif; ]]
			</div>