<?php
/**
 * @file
 * This file includes page callbacks for Meds reports module.
 */

/**
 * Performance center page callback.
 */
function performance_test_page_callback($form, $form_state, $current_category) {
  $context = array('context' => PERFORMANCE_TEST_TRANSLATE_CONTEXT);

  drupal_set_title(t('Drupal Performance center', array(), $context));

  // Get all performance test plugins.
  $tests      = performance_test_get_test_plugins();
  $categories = performance_test_get_available_categories();

  foreach ($categories as $category) {
    if ($category['type_name'] == $current_category) {
      $form['title'] = array(
        '#markup' => '<h2>' . $category['page_title'] . '</h2>',
      );
    }
    continue;
  }

  $t = get_t();
  if (!empty($tests)) {
    foreach ($tests as $test) {
      // Create an instance for the plugin.
      $plugin = PerformanceTestManager::factory($test);
      $test_category = $plugin->testCategory();

      // Move to the next test plugin if current has wrong category.
      if ($current_category != $test_category) {
        continue;
      }

      $class = $test['handler']['class'];
      if (!isset($form[$current_category])) {
        $form[$class] = array(
          '#type' => 'fieldset',
          '#title' => $t($test['name'], array(), $context),
          '#collapsible' => FALSE,
          '#collapsed' => FALSE,
        );
      }

      // Add form elements.
      $iterations = !empty($plugin->iterations) ? $plugin->iterations : PERFORMANCE_TEST_ITERATIONS;
      $callbacks  = $plugin->exportResults();
      $output = array();
      foreach ($callbacks as $callback) {
        if (is_callable(array($plugin, $callback))) {
          performance_test_start_timer_for_variant($callback);
          $callback_data = $plugin->$callback($iterations);
          performance_test_read_timer_for_variant($callback_data, $callback);

          $output[] = $callback_data;
        }
      }

      performance_test_render_plugin_results($output);
    }
  }
}

/**
 * Render results of code execution.
 */
function performance_test_render_plugin_results($output) {
  dpm($output);
}
