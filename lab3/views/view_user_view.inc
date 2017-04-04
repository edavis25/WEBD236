%% views/header.inc %%

<h1>{{ $title }}</h1>

<table>
    <tr>
        <td>First Name: </td>
        <td>{{ $user->getFirstName() }}</td>
    </tr>
    <tr>
        <td>Last Name: </td>
        <td>{{ $user->getLastName() }}</td>
    </tr>
    <tr>
        <td>E-mail: </td>
        <td>{{ $user->getEmail() }}</td>
    </tr>
</table>

<br />

[[ if ($ownsAccount ||  Authenticator::instance() -> can('user_edit')) : ]]
<a href="@@user/edit_user/{{ $user->getId() }}@@">[ Edit ]</a>
<div class="delete-wrapper">
    <a href="#" class="delete-button">[ Delete ]</a>&nbsp;
    <div class="confirm-delete" style="display: none;"> 
        <a href="@@user/delete_user/{{ $user->getId() }}@@"> yes</a> / <a href="#" class="delete-button">no</a>
    </div>
</div>
[[ endif; ]]

<h2>Questions By {{ $user->getFirstName() . " " . $user->getLastName() }}</h2>

[[ foreach ($questions as $question): ]]
    %% views/question_preview.inc %%
[[ endforeach ]]

%% views/footer.inc %%


