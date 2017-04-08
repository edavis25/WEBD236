%% views/header.inc %%
<h1>{{$title}}</h1>

<table class="users-table">
[[ foreach ($users as $user) : ]]
    <tr>
        <td><a href="@@user/view_user/{{$user->getId()}}@@">View</a></td>
        <td><a href="@@user/user_groups/{{$user->getId()}}@@">Groups</td>
        <td>
            <div class="delete-wrapper">
                <a href="##" class="delete-button"> Delete</a>&nbsp;
                <div class="confirm-delete" style="display: none;">
                    <a href="@@user/delete_user/{{$user->getId()}}@@">yes</a> / <a href="##" class="delete-button">no</a>
                </div>
            </div>
        <td>{{User::getFullName($user->getId())}}</td>
    </tr>
[[ endforeach; ]]
</table>

<br />
<a href="@@admin@@">&lt;&lt; Back</a>
%% views/footer.inc %%
