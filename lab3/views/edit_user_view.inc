%% views/header.inc %%

<h1>{{ $title }}</h1>

<div id="errors">
	{{ isset($errors) ? $errors."<br />" : '' }}
</div>

<br />

<form action="@@{{ $form_action }}@@" method="post">
	<label for="first-name">First Name:</label><br />
	<input type="text" id="first-name" name="first-name" class="full-width" value="{{ isset($inputs['FirstName']) ? $inputs['FirstName'] : '' }}" />
	
	<label for="last-name">Last Name:</label><br />
	<input type="text" id="last-name" name="last-name" class="full-width" value="{{ isset($inputs['LastName']) ? $inputs['LastName'] : '' }}" />
	<!-- input type="text" id="last-name" name="last-name" class="full-width" value="{{ $inputs['LastName'] }}" / -->
	
	<label for="username">Email Address:</label><br />
	<input type="text" id="username" name="username" class="full-width" value="{{ isset($inputs['Email']) ? $inputs['Email'] : '' }}" />
	<!-- input type="text" id="username" name="username" class="full-width" value="{{ $inputs['Email'] }}" / -->
	
	<label for="password">Password:</label><br />
	<input type="text" id="password" name="password" class="full-width" value="{{ isset($inputs['Password']) ? $inputs['Password'] : '' }}" />
	
	<input type="submit" id="login-submit" name="login-submit" value="{{ $button_text }}" />
</form>

%% views/footer.inc %%
