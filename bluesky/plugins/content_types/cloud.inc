<?php
/**
 * @file
 * cloud.inc
 */
 
 /**
  * Plugin definition
  */
 $plugin = array(
	'single' => TRUE,
	'title' => t('Floating Cloud'),
	'description' => t('The floating Cloud for a node'),
	'required context' => new ctools_context_required(t('Node'), 'node'),
	'category' => t('Widgets'),
	'defaults' => array(
		'override_title' => FALSE,
		'override_title_text' => '',
		'widget' => '',
	),
);

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

function bluesky_cloud_content_type_edit_form(&$form, &$form_state) {
}

function bluesky_cloud_content_type_edit_form_submit(&$form, &$form_state) {
}

function bluesky_cloud_content_type_admin_title($subtype, $conf, $context) {
	return t('"@s" cloud', array('@s' => $context->indentifier));
}