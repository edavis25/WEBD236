%% views/header.inc %%
<h1>{{$title}}</h1>

<h2>Granted Permissions</h2>
<table class="group-table">
[[ foreach ($grantedPerms as $permission) : ]]
    <tr>
        <td><a href="@@group/revoke/{{$group->getId()}}/{{$permission->getId()}}@@">Revoke</a></td>
        <td>{{$permission->getName()}}</td>
    </tr>
[[ endforeach; ]]
</table>

<h2>Available Permissions</h2>
<table class="group-table">
[[ foreach ($availablePerms as $permission) : ]]
    <tr>
        <td><a href="@@group/grant/{{$group->getId()}}/{{$permission->getId()}}@@">Grant</a></td>
        <td>{{$permission->getName()}}</td>
    </tr>
[[ endforeach; ]]
</table>

<br />
<a href="@@group/manage_groups@@">&lt;&lt; Back</a>
%% views/footer.inc %%