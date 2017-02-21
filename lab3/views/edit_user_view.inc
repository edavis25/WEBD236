%% views/header.inc %%

<?php include_once 'views/navigation.inc' ?>

<h1>{{ $title }}</h1>

<div id="errors">
	{{ isset($errors) ? $errors."<br />" : '' }}
</div>
<br />
<form action="@@{{ $form_action }}@@" method="post">
	<label for="first-name">First Name:</label><br />
	<input type="text" id="first-name" name="first-name" class="full-width" value="{{ isset($inputs['first_name']) ? $inputs['first_name'] : '' }}" />
	<br /><br />
	<label for="last-name">Last Name:</label><br />
	<input type="text" id="last-name" name="last-name" class="full-width" value="{{ isset($inputs['last_name']) ? $inputs['last_name'] : '' }}" />
	<br /><br />
	<label for="username">Email Address:</label><br />
	<input type="text" id="username" name="username" class="full-width" value="{{ isset($inputs['username']) ? $inputs['username'] : '' }}" />
	<br /><br />
	<label for="password">Password:</label><br />
	<input type="text" id="password" name="password" class="full-width" value="{{ isset($inputs['password']) ? $inputs['password'] : '' }}" />
	<br /><br />
	<input type="submit" id="login-submit" name="login-submit" value="{{ $button_text }}" />
</form>

%% views/footer.inc %%
