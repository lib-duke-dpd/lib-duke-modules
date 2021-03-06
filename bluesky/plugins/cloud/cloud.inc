<?php
/**
 * @file
 * Plugin to handle the lone 'cloud' appearing in the bluesky
 */
 
/**
 * Plugins are described by creating a $plugin array which allows the local 
 * actions template variables to be embedded into a panel
 */
$plugin = array(
	'single' => TRUE,
	'title' => t('Cloud output'),
	'icon' => 'icon_node.png',
	'description' => t('The single cloud in the blue sky.'),
	'context' => 'bluesky_cloud_context_callback',
);

function bluesky_cloud_context_callback() {
	watchdog('bluesky_cloud_context_callback', '');
}

/**
 * Render the custom content type
 */
function bluesky_cloud_content_type_render($subtype, $conf, $panel_args, $context) {
	$block = new stdClass();
	$block->module	= 'cloud';
	$block->title	= t('My Cloud Title');
	$block->content	= t('I can float in this.');
	$block->delta	= $conf['nid'];
	
	return $block;
}

function bluesky_cloud_content_type_admin_title($subtype, $conf, $context) {
	return t('"@s" cloud', array('@s' => $context->indentifier));
}