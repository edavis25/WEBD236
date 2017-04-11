%% views/header.inc %%

<h1>{{ $title }}</h1>

%% views/errors.inc %%

<br />

<form action="@@login@@" method="post">
    <label for="username">Email:</label><br />
    <input type="text" id="username" name="username" class="full-width" />
    <br />
    <label for="password">Password:</label><br />
    <input type="text" id="password" name="password" class="full-width" />
    <br />
    <input type="submit" id="login-submit" name="login-submit" value="Login" />
    <a href="@@login/forgot_password@@" class="float-right">Forgot your password?</a>
</form>

%% views/footer.inc %%
