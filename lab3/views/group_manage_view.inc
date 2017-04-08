%% views/header.inc %%

<h1>{{ $title }}</h1>

<h3>Create New Group</h3>

%% views/errors.inc %%

<form method="POST" action="@@group/add_group@@">
    <label for="name">Group name:</label><br />
    <input type="text" name="name" />
    <input type="submit" value="Add Group" />    
</form>
<hr />
<h3>Manage Existing Groups</h3>
    [[ foreach($groups as $group) :  ]]
    <table class="group-table">
        <tr><th colspan="3">{{ $group -> getName() }}</th></tr>
        <tr>
            <td><a href="@@group/members/{{$group->getId()}}@@"> Members </a></td>
            <td><a href="@@group/permissions/{{$group->getId()}}@@"> Permissions </a></td>
            <td>
                <div class="delete-wrapper">
                    <a href="##" class="delete-button"> Delete</a>&nbsp;
                    <div class="confirm-delete" style="display: none;"> 
                        <a href="@@group/delete/{{$group->getId()}}@@">yes</a> / <a href="##" class="delete-button">no</a>
                    </div>
                </div>
            </td>
        </tr>
    </table>
    [[ endforeach; ]]

<br />
<a href="@@admin@@">&lt;&lt; Back</a>

%% views/footer.inc %%

