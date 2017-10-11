<?php

/**
 * @file
 *   Translation template extractor module drush integration.
 */

/**
 * Implements hook_drush_command().
 *
 * @see drush_parse_command() for a list of recognized keys.
 *
 * @return
 *   An associative array describing our command.
 */
function potx_drush_command() {
  $items['potx'] = array(
    'callback' => 'potx_drush_extract',
    'description' => 'Extract translatable strings from Drupal source code.',
    'arguments' => array(
      'mode' => 'potx output mode e.g. single multiple core',
    ),
    'options' => array(
      'modules' => 'Comma delimited list of modules to extract translatable strings from.',
      'files' => 'Comma delimited list of files to extract translatable strings from.',
      'folder' => 'Folder to begin translation extraction in. When no other option is set this defaults to current directory.',
      'api' => 'Drupal core version to use for extraction settings.',
      'language' => 'language to include in the po file',
    ),
    'examples' => array(
      'potx single' => 'Extract translatable strings from applicable files in current directory and write to single output file',
      'potx multiple --modules=example' => 'Extract translatable strings from applicable files of example module and write to module-specific output file.',
      'potx --files=sites/all/modules/example/example.module' => 'Extract translatable strings from example.module and write to single output file.',
      'potx single --api=8 --folder=projects/drupal/8' => 'Extract strings from folder projects/drupal/8 using API version 8.',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_NONE,
  );
  return $items;
}

/**
 * Implementation of hook_drush_help().
 *
 * This function is called whenever a drush user calls
 * 'drush help potx'.
 *
 * @param
 *   A string with the help section (prepended with 'drush:').
 *
 * @return
 *   A string with the help text for our command.
 */
function potx_drush_help($section) {
  if ($section == 'drush:potx') {
    $help = dt('Generates translation templates from the given Drupal source code in the current working directory.');
    $help .= "\n\n". dt('Possible potx modes are:');
    $help .= "\n". dt(' single    Single file output mode, every file folded into the single output file (default).');
    $help .= "\n". dt(' multiple  Multiple file output mode, .info files folded into module .pot files.');
    $help .= "\n". dt(' core      Drupal core output mode, .info files folded into general.pot.');
    $help .= "\n\n". dt('If no files are specified, potx will autodiscover files from the current working directory. You can specify concrete files to look at to limit the scope of the operation.');
    return $help;
  }
}

/**
 * Drush command callback.
 */
function potx_drush_extract($mode = NULL) {
  \Drupal::service('potx.commands')->potx($mode,  [
    'modules' => drush_get_option('modules'),
    'files' => drush_get_option('files'),
    'folder' => drush_get_option('folder'),
    'api' => drush_get_option('api'),
    'language' => drush_get_option('language'),
  ]);
}
