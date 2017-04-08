<?php
include_once 'include/util.inc';
include_once 'include/Authenticator.inc';
include_once 'models/Group.inc';

function get_manage_groups($params) {
    Authenticator::instance() -> ensure('admin_page');
    $groups = Group::findAll();
    
    // @formatter: off
    renderTemplate(
        "views/group_manage_view.inc", 
        array(
            'title' => 'Group Management',
            'groups' => $groups
        )
    );
    // @formatter: on
}

function get_members($params) {
    Authenticator::instance() -> ensure('admin_page');
    
    $id = safeParam($params, 0, false);
    if (!$id) {
        die("Error: No group selected.");
    }
    
    $group = Group::findById($id);
    $members = $group -> getMembers();
    $nonmembers = $group -> getNonMembers();
    
    // @formatter: off
    renderTemplate(
        "views/group_members_view.inc",
        array(
            'title' => $group->getName() . " Group",
            'group' => $group,
            'members' => $members,
            'nonmembers' => $nonmembers
        )
    );
    // @formatter: on
}

function get_remove_member($params) {
    Authenticator::instance() -> ensure('admin_page');
    
    $groupId = safeParam($params, 0, false);
    $userId = safeParam($params, 1, false);
   
    $group = Group::findById($groupId);
    $user = User::retrieveUserById($userId);
    
    if (!$group || !$user) {
        die("Error: No group or user selected.");
    }
    
    $group -> removeUser($user);
    redirectRelative("group/members/{$group->getId()}");
}

function get_include_member($params) {
    Authenticator::instance() -> ensure('admin_page');
    
    $groupId = safeParam($params, 0, false);
    $userId = safeParam($params, 1, false);
    
    $group = Group::findById($groupId);
    $user = User::retrieveUserById($userId); 
    
    if (!$group || !$user) {
        die("Error: No group or user selected.");
    }
    
    $group ->addUser($user);
    redirectRelative("group/members/{$group->getId()}");
}

function get_permissions($params) {
    Authenticator::instance() -> ensure('admin_page');
    
    $id = safeParam($params, 0, false);
    if (!$id) {
        die("Error: No group selected.");
    }
    
    $group = Group::findById($id);
    $grantedPerms = $group ->getPermissions();
    $availablePerms = $group ->getNonPermissions();
    
    // @formatter: off
    renderTemplate(
        "views/group_permissions_view.inc",
        array(
            'title' => "{$group->getName()} Group Permissions",
            'grantedPerms' => $grantedPerms,
            'availablePerms' => $availablePerms,
            'group' => $group
        )
    );
    // @formatter: on
}

function get_grant($params) {
    Authenticator::instance() -> ensure('admin_page');
    $groupId = safeParam($params, 0, false);
    $permId = safeParam($params, 1, false);
    
    $group = Group::findById($groupId);
    $permission = Permission::findById($permId);
    if (!$group ||  !$permission) {
        die("Error: Group or permission not defined.");
    }
    
    $group -> addPermission($permission);
    redirectRelative("group/permissions/{$group->getId()}");
}

function get_revoke($params) {
    Authenticator::instance() -> ensure('admin_page');
    $groupId = safeParam($params, 0, false);
    $permId = safeParam($params, 1, false);
    
    $group = Group::findById($groupId);
    $permission = Permission::findById($permId);
    if (!$group ||  !$permission) {
        die("Error: Group or permission not defined.");
    }
    
    $group -> removePermission($permission);
    redirectRelative("group/permissions/{$group->getId()}");
}

function get_delete($params) {
    Authenticator::instance() -> ensure('admin_page');
    $id = safeParam($params, 0, false);
    if (!$id) {
        die("Error: No group selected.");
    }
    
    $group = Group::findById($id);
    $group -> delete();
    
    redirectRelative("group/manage_groups");
}

function post_add_group($params) {
    Authenticator::instance() -> ensure('admin_page');
    
    $name = safeParam($_POST, 'name', false);
    
    $group = new Group(null, $name);
    $validator = $group -> validate();
    if ($validator -> hasErrors()) {
        get_manage_groups(null);
        die;
    }
    
    $group -> insert();
    redirectRelative("group/manage_groups");
}
