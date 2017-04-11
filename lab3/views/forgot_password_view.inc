%% views/header.inc %%

<h1>{{$title}}</h1>
<br />
<p>Enter the email address associated with your account.</p>
%% views/errors.inc %%
<form method="post" action="" >
    <label for="email">Email:</label><br />
    <input type="text" name="email" class="full-width"/><br /><br />
    <input type="submit" value="Send Email"  />
</form>
%% views/footer.inc %%