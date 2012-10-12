<?php

/**
 * Callback function to supply a list of content types.
 */
function bluesky_cloud_ctools_content_types() {
	return array(
		'single' => TRUE,
		'title' => t('Cloud output'),
		'icon' => 'icon_node.png',
		'description' => t('The single cloud in the blue sky.'),
		'required context' => new ctools_context_required(t('Node'), 'node'),
		'category' => t('Node'),
	);
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