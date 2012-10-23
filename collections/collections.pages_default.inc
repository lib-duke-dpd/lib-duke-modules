<?php

/**
 * Implementation of hook_default_page_manager_pages().
 */
function collections_default_page_manager_pages() {
	$page = array();
	$path = drupal_get_path('module', 'collections') . '/pages';
	include_once $path . '/collections-main.inc';
	$pages[$page->name] = $page;
	
	#$files = drupal_system_listing('.inc$', $path, 'name', 0);
	#foreach ($files as $file) {
	#	include_once $file->filename;
	#	$pages[$page->name] = $page;
	#}
	return $pages;
}
