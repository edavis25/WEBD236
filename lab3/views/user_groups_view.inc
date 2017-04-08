%% views/header.inc %%
<h1>{{$title}}</h1>

<h2>Member of</h2>
<table class="group-table">
[[ foreach ($member as $group) : ]]
    <tr>
        <td><a href="@@group/remove_member/{{$group->getId()}}/{{$user->getId()}}@@">Leave</a></td>
        <td>{{$group->getName()}}</td>
    </tr>
[[ endforeach; ]]
</table>

<h2>Available groups</h2>
<table class="group-table">
[[ foreach ($nonmember as $group) : ]]
    <tr>
        <td><a href="@@group/include_member/{{$group->getId()}}/{{$user->getId()}}@@">Join</a></td>
        <td>{{$group->getName()}}</td>
    </tr>
[[ endforeach; ]]
</table>

<br />
<a href="@@user/manage_users@@">&lt;&lt; Back</a>
%% views/footer.inc %%