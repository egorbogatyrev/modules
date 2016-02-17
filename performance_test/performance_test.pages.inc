<?php
/**
 * @file
 * This file includes page callbacks for Meds reports module.
 */

/**
 * Performance center page callback.
 */
function performance_test_page_callback($category) {
  $context = array('context' => PERFORMANCE_TEST_TRANSLATE_CONTEXT);

  drupal_set_title(t('Drupal Performance center', array(), $context));

  // Get all performance test plugins.
  $tests      = performance_test_get_test_plugins();
  $categories = performance_test_get_available_categories();

  foreach ($categories as $category) {
    if ($category['type_name'] == $category) {
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
      if ($category != $test_category) {
        continue;
      }

      $class = $test['handler']['class'];
      if (!isset($form[$category])) {
        $form[$class] = array(
          '#type' => 'fieldset',
          '#title' => $t($test['name'], array(), $context),
          '#collapsible' => FALSE,
          '#collapsed' => FALSE,
        );
      }

      // Add form elements.
      $iterations = !empty($plugin->iterations) ? $plugin->limit : PERFORMANCE_TEST_ITERATIONS;
      $callbacks  = $plugin::exportResults();

      foreach ($callbacks as $id => $callback) {
        if (is_callable($callback)) {
          performance_test_start_timer_for_variant($id);
          $callback_data = $callback($iterations);
          performance_test_start_timer_for_variant($callback_data, $id);

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
