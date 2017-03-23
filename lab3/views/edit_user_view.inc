%% views/header.inc %%

<h1>{{ $title }}</h1>

<div id="errors">
    {{ isset($errors) ? $errors."<br />" : '' }}
</div>

<br />

<form action="@@{{ $form_action }}@@" method="post">
    <label for="first-name">First Name:</label><br />
    <input type="text" id="first-name" name="first-name" class="full-width" value="{{ $user->getFirstName() }}" />

    <label for="last-name">Last Name:</label><br />
    <input type="text" id="last-name" name="last-name" class="full-width" value="{{ $user->getLastName() }}" />

    <label for="username">Email Address:</label><br />
    <input type="text" id="username" name="username" class="full-width" value="{{ $user->getEmail() }}" />

    <label for="password">Password:</label><br />
    <input type="text" id="password" name="password" class="full-width" value="{{ $user->getPassword() }}" />

    <input type="hidden" id="user-id" name="user-id" value="{{ $user->getId() }}" />
    
    <input type="submit" id="login-submit" name="login-submit" value="{{ $button_text }}" />
</form>

%% views/footer.inc %%
